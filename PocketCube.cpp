#include "PocketCube.h"
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>


PocketCube::PocketCube()
{
    srand(time(NULL));
    create_transitions();
}


void PocketCube::create_transitions()
{
    transitions = std::vector<std::vector<int>>(state_cnt, std::vector<int>(9));

    std::vector<int> permutation{0, 1, 2, 3, 4, 5, 6};
    std::vector<int> orientation{0, 0, 0, 0, 0, 0, 0};
    do
    {
        int perm_index = permutation_to_index(permutation);
        for (int orient_index = 0; orient_index < 729; orient_index++)
        {
            index_to_orientation_dependent(orient_index, orientation);
            for (int i = 0; i < 4; i ++)
            {
                move_U(permutation, orientation);
                if (i < 3)
                {
                    transitions[perm_index * 729 + orient_index][i] =
                            permutation_to_index(permutation) * 729 + orientation_to_index_dependent(orientation);
                }
            }

            for (int i = 0; i < 4; i ++)
            {
                move_R(permutation, orientation);
                if (i < 3)
                {
                    transitions[perm_index * 729 + orient_index][i + 3] =
                            permutation_to_index(permutation) * 729 + orientation_to_index_dependent(orientation);
                }
            }

            for (int i = 0; i < 4; i ++)
            {
                move_F(permutation, orientation);
                if (i < 3)
                {
                    transitions[perm_index * 729 + orient_index][i + 6] =
                            permutation_to_index(permutation) * 729 + orientation_to_index_dependent(orientation);
                }
            }
        }

    } while (std::next_permutation(permutation.begin(), permutation.end()));
}


int PocketCube::permutation_to_index(std::vector<int> const& arr)
{
    int n = arr.size();
    int index = 0;
    for (int i = 0; i < n; i++)
    {
        index *= n - i;
        for (int j = i; j < n; j++)
        {
            if (arr[i] > arr[j])
            {
                index += 1;
            }
        }
    }
    return index;
}


int PocketCube::orientation_to_index_dependent(std::vector<int> const& arr)
{
    int n = arr.size();
    int index = 0;
    for (int i = 0; i < n - 1; i++)
    {
        index = index * 3 + arr[i];
    }
    return index;
}


void PocketCube::index_to_orientation_dependent(int index, std::vector<int> & arr)
{
    int n = arr.size();
    arr[n - 1] = 0;
    for (int i = n - 2; i >= 0; i--)
    {
        arr[i] = index % 3;
        arr[n - 1] -= arr[i];
        if (arr[n - 1] < 0)
        {
            arr[n - 1] += 3;
        }
        index /= 3;
    }
}


/*
 *     3---4
 *    /|  /|
 *   *-|-0 |
 *   | 6---5
 *   |/  |/
 *   2---1
 */


void PocketCube::move_R(std::vector<int> & permutation, std::vector<int> & orientation)
{
    int tmp = permutation[0];
    permutation[0] = permutation[4];
    permutation[4] = permutation[5];
    permutation[5] = permutation[1];
    permutation[1] = tmp;

    tmp = orientation[0];
    orientation[0] = (orientation[4] + 1) % 3;
    orientation[4] = (orientation[5] + 2) % 3;
    orientation[5] = (orientation[1] + 1) % 3;
    orientation[1] = (tmp + 2) % 3;
}


void PocketCube::move_U(std::vector<int> & permutation, std::vector<int> & orientation)
{
    int tmp = permutation[3];
    permutation[3] = permutation[6];
    permutation[6] = permutation[5];
    permutation[5] = permutation[4];
    permutation[4] = tmp;

    tmp = orientation[3];
    orientation[3] = orientation[6];
    orientation[6] = orientation[5];
    orientation[5] = orientation[4];
    orientation[4] = tmp;
}


void PocketCube::move_F(std::vector<int> & permutation, std::vector<int> & orientation)
{
    int tmp = permutation[6];
    permutation[6] = permutation[2];
    permutation[2] = permutation[1];
    permutation[1] = permutation[5];
    permutation[5] = tmp;

    tmp = orientation[6];
    orientation[6] = (orientation[2] + 1) % 3;
    orientation[2] = (orientation[1] + 2) % 3;
    orientation[1] = (orientation[5] + 1) % 3;
    orientation[5] = (tmp + 2) % 3;
}


void PocketCube::scramble()
{
    current = rand() % state_cnt;
}


bool PocketCube::is_solved()
{
    return current == 0;
}


void PocketCube::do_random_move()
{
    current = transitions[current][rand() % 9];
}
