#ifndef GA_4_CAMOUFLAGE_H
#define GA_4_CAMOUFLAGE_H

#include <vector>
#include <iostream>

#include "hsl.h"
#include "algos.h"
#include "raylib.h"

using PopulationVector = std::vector<HSLColor>;
using SizeTVector = std::vector<std::size_t>;

struct Stats
{
    std::size_t GENERATION = 0;
    double MUTATION_RATE = 0;
    double ELITE_RATIO = 0;
    HSLColor BACKGROUND = {0, 0, 0};
    std::size_t TOP_FITNESS_SCORE = 0;
    std::size_t MEDIAN_FITNESS_SCORE = 0;
    std::size_t WORST_FITNESS_SCORE = 0;
};

class GA
{
private:
    PopulationVector population;
    SizeTVector fitnessScores;
    SizeTVector sortedFitnessScoresIndices;

    // ! GENERATION
    void generateRandomPopulation();

    // ! FITNESS CALCULATION
    int calculateHueDifference(int h1, int h2);
    void calculatePopulationFitness();
    void calculateSortedFitnessScoresIndices();

    // ! CROSSOVER
    HSLColor breed(const HSLColor &elite, const HSLColor &normie, const std::size_t eliteFitnessScore, const std::size_t normieFitnessScore);
    void getNextGeneration();

public:
    std::size_t GENERATION = 0;
    std::size_t ROW_COUNT = 0;
    std::size_t COL_COUNT = 0;
    std::size_t POPULATION_SIZE = 0;

    double MUTATION_RATE = 0.0005;
    double ELITE_RATIO = 0.05;
    HSLColor BACKGROUND = {0, 0, 0};

    // ! UI STATE
    bool border = false;

    // ! CONSTRUCTORS
    GA(std::size_t row_count, std::size_t col_count, double mutation_rate, HSLColor background);

    // ! RENDERING
    void Update();
    void Render(int xPos, int yPos, int width, int height);

    // ! STATS
    Stats Stat();
};

#endif