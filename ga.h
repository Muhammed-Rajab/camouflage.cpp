#ifndef GA_4_CAMOUFLAGE_H
#define GA_4_CAMOUFLAGE_H

#include <vector>
#include <iostream>

#include "hsl.h"
#include "algos.h"
#include "raylib.h"

using PopulationVector = std::vector<HSLColor>;
using SizeTVector = std::vector<std::size_t>;

PopulationVector generateRandomPopulation(std::size_t count);

int calculateHueDifference(int h1, int h2);

SizeTVector calculatePopulationFitness(const PopulationVector &population, const HSLColor &background);

SizeTVector getSortedFitnessScoresIndices(const SizeTVector &fitnessScore);

void displayFitnessScore(const SizeTVector &fitnessScore);

void renderPopulation(const PopulationVector &population, int xPos, int yPos, int width, int height, std::size_t ROW_COUNT, std::size_t COL_COUNT, bool border);

HSLColor singlePointCrossOver(const HSLColor &elite, const HSLColor &normie, const std::size_t eliteFitnessScore, const std::size_t normieFitnessScore);

PopulationVector getNextGeneration(const PopulationVector &population, const SizeTVector &fitnessScore, const SizeTVector &sortedFitnessScoreIndices);

#endif