#ifndef GA_4_CAMOUFLAGE_H
#define GA_4_CAMOUFLAGE_H

#include <vector>
#include <iostream>

#include "hsl.h"
#include "raylib.h"

using PopulationVector = std::vector<HSLColor>;
using SizeTVector = std::vector<std::size_t>;

PopulationVector generateRandomPopulation(std::size_t count);

int calculateHueDifference(int h1, int h2);

SizeTVector calculatePopulationFitness(const PopulationVector &population, const HSLColor &background);

SizeTVector getSortedFitnessScoresIndices(const SizeTVector &fitnessScore);

void displayFitnessScore(const SizeTVector &fitnessScore);

void renderPopulation(const PopulationVector &population, int GRID_WIDTH, int GRID_HEIGHT, std::size_t ROW_COUNT, std::size_t COL_COUNT, int OFFSET_X, int OFFSET_Y);

#endif