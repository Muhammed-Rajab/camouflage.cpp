#include <ctime>
#include <cstdlib>
#include <algorithm>

#include "algos.h"

int GenerateRandomValue(int min, int max)
{
    return min + rand() % (max - min + 1);
}

std::vector<std::size_t> argsort(const std::vector<std::size_t> &arr)
{
    std::vector<std::size_t> indices(arr.size());
    for (std::size_t index = 0; index < arr.size(); ++index)
    {
        indices[index] = index;
    }

    std::sort(indices.begin(), indices.end(), [&arr](std::size_t a, std::size_t b)
              { return arr[a] > arr[b]; });

    return indices;
}
