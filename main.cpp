#include <iostream>
#include <ctime>
#include "PocketCube.h"
#include <algorithm>

using namespace std;

int main() {
    PocketCube cube;


    vector<int> results;
    vector<double> times;
    for (int id = 0; id < 100; id++) {
        cube.scramble();

        cout << "Start solving" << endl;
        std::clock_t start = std::clock();
        int i = 0;
        while (!cube.is_solved()) {
            i++;
            cube.do_random_move();

            if (i % 1000000 == 0)
                cout << i << " moves" << endl;
        }

        double s = (std::clock() - start) / (double) (CLOCKS_PER_SEC);
        results.push_back(i);
        times.push_back(s);
        cout << "Solved after " << i << " moves in " << s << " seconds (" << i / s << " / sec)" << endl;
    }

    cout << endl;
    long long int total = accumulate(results.begin(), results.end(), 0LL);
    double total_time = accumulate(times.begin(), times.end(), 0.0);

    cout << "Average moves: " << total / 100.0 << endl;
    cout << "Average time:  " << total_time / 100.0 << endl;
}