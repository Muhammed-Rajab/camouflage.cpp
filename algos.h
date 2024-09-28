#ifndef ALGOS_4_CAMOUFLAGE_H
#define ALGOS_4_CAMOUFLAGE_H

#include <cstdlib>
#include <ctime>

int GenerateRandomValue(int min, int max)
{
    return min + rand() % (max - min + 1);
}

#endif