#ifndef ALGOS_4_CAMOUFLAGE_H
#define ALGOS_4_CAMOUFLAGE_H

#include <ctime>
#include <cstdlib>
#include <algorithm>

// #include "ga.h"

int GenerateRandomValue(int min, int max)
{
    return min + rand() % (max - min + 1);
}

// SizeTVector argsort(const SizeTVector &arr)
// {
//     SizeTVector indices(arr.size());
//     for (std::size_t index = 0; index < arr.size(); ++index)
//     {
//         indices[index] = index;
//     }

//     std::sort(indices.begin(), indices.end(), [&arr](std::size_t a, std::size_t b)
//               { return arr[a] > arr[b]; });

//     return indices;
// }

#endif