#include <vector>
#include <iostream>

#include "hsl.h"
#include "algos.h"
#include "raylib.h"
#include "ga.h"

PopulationVector generateRandomPopulation(std::size_t count)
{
    std::vector<HSLColor> population(count);

    for (std::size_t index = 0; index < count; ++index)
    {
        // ! POPULATION WILL HAVE DIFFERENT HUE ONLY
        // ! BUT SAME SATURATION AND LIGHTNESS, TO KEEP THINGS SIMPLE
        population.at(index) = HSLColor{
            GenerateRandomValue(0, 360),
            // GenerateRandomValue(0, 1000) / 1000.0f,
            0.5,
            // GenerateRandomValue(0, 1000) / 1000.0f,
            0.5,
        };
    }

    return population;
}

int calculateHueDifference(int h1, int h2)
{
    int deltaH = std::abs(h1 - h2);
    return std::min(deltaH, 360 - deltaH);
}

SizeTVector calculatePopulationFitness(const PopulationVector &population, const HSLColor &background)
{
    SizeTVector fitnessScores;
    fitnessScores.reserve(population.size());

    for (const HSLColor &individual : population)
    {
        fitnessScores.push_back(360 - calculateHueDifference(background.h, individual.h));
    }

    return fitnessScores;
}

SizeTVector getSortedFitnessScoresIndices(const SizeTVector &fitnessScore)
{
    return argsort(fitnessScore);
}

void displayFitnessScore(const SizeTVector &fitnessScore)
{
    for (const std::size_t &score : fitnessScore)
    {
        std::cout << "Score: " << score << "\n";
    }
}

void renderPopulation(const PopulationVector &population, int GRID_WIDTH, int GRID_HEIGHT, std::size_t ROW_COUNT, std::size_t COL_COUNT, int OFFSET_X, int OFFSET_Y)
{
    std::size_t pos = 0;
    for (std::size_t row = 0; row < ROW_COUNT; ++row)
    {
        const int y = row * GRID_HEIGHT + OFFSET_Y;
        for (std::size_t col = 0; col < COL_COUNT; ++col)
        {
            const int x = col * GRID_WIDTH + OFFSET_X;
            const int index = (COL_COUNT * row + col);

            const HSLColor &hsl = population.at(index);
            const RGBColor &rgb = HSLToRGB(hsl.h, hsl.s, hsl.l);

            DrawRectangle(x, y, GRID_WIDTH, GRID_HEIGHT, Color{(unsigned char)rgb.r, (unsigned char)rgb.g, (unsigned char)rgb.b, 255});

            pos += 3;
        }
    }
}

PopulationVector getNextGeneration(const PopulationVector &population, const SizeTVector &fitnessScore, const SizeTVector &sortedFitnessScoreIndices)
{
    const double ELITE_RATIO = 0.05;
    std::size_t maxEliteIndex = static_cast<std::size_t>(ELITE_RATIO * sortedFitnessScoreIndices.size());

    PopulationVector newPopulation(population.size());

    // Append elites to population
    for (std::size_t index = 0; index < maxEliteIndex; ++index)
    {
        newPopulation.at(index) = (population.at(sortedFitnessScoreIndices.at(index)));
    }

    for (std::size_t index = maxEliteIndex; index < population.size(); ++index)
    {
        const std::size_t eliteIndex = GenerateRandomValue(0, maxEliteIndex - 1);

        const HSLColor elite = population.at(sortedFitnessScoreIndices.at(eliteIndex));

        const std::size_t normieIndex = GenerateRandomValue(maxEliteIndex, sortedFitnessScoreIndices.size() - 1);

        const HSLColor normie = population.at(sortedFitnessScoreIndices.at(normieIndex));

        const HSLColor child = singlePointCrossOver(elite, normie, fitnessScore.at(sortedFitnessScoreIndices.at(eliteIndex)), fitnessScore.at(sortedFitnessScoreIndices.at(normieIndex)));

        newPopulation.at(index) = child;

        // std::cout << "index:" << index << "\n";
    }

    return newPopulation;
}

HSLColor singlePointCrossOver(const HSLColor &elite, const HSLColor &normie, const std::size_t eliteFitnessScore, const std::size_t normieFitnessScore)
{

    double totalFitness = eliteFitnessScore + normieFitnessScore;
    double w1 = eliteFitnessScore / totalFitness;
    double w2 = normieFitnessScore / totalFitness;

    int newHue = (elite.h * w1 + normie.h * w2);

    const double MUTATION_RATE = 0.0005;
    if (rand() % 100 < MUTATION_RATE * 100)
    {
        int mutationValue = GenerateRandomValue(-360, 360);
        newHue = abs((newHue + mutationValue)) % 360;
    }

    return HSLColor{
        newHue % 360,
        0.5,
        0.5,
    };
}