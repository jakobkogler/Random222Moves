#ifndef RANDOM222MOVES_POCKETCUBE_H
#define RANDOM222MOVES_POCKETCUBE_H

#include <vector>


class PocketCube {
private:
    int state_cnt = 3674160; // 3^6 * 7!
    std::vector<std::vector<int>> transitions;

    int current = 0;

    void create_transitions();
    int permutation_to_index(std::vector<int> const& arr);
    int orientation_to_index_dependent(std::vector<int> const& arr);
    void index_to_orientation_dependent(int index, std::vector<int> & arr);
    void move_R(std::vector<int> & permutation, std::vector<int> & orientation);
    void move_U(std::vector<int> & permutation, std::vector<int> & orientation);
    void move_F(std::vector<int> & permutation, std::vector<int> & orientation);

public:
    PocketCube();
    void scramble();
    bool is_solved();
    void do_random_move();
};


#endif //RANDOM222MOVES_POCKETCUBE_H
