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
        fitnessScores.push_back(calculateHueDifference(background.h, individual.h));
    }

    return fitnessScores;
}

SizeTVector getSortedFitnessScoresIndices(const SizeTVector &fitnessScore)
{
    // return argsort(fitnessScore);
    return fitnessScore;
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

HSLColor singlePointCrossOver(const HSLColor &elite, const HSLColor &normie)
{
    int diff = abs(elite.h - normie.h);
    int newHue = 0;
    if (diff > 180)
    {
        // If the hues are on opposite sides of the color wheel
        newHue = (elite.h + normie.h + 360) / 2 % 360;
    }
    else
    {
        // Regular average for small differences
        newHue = (elite.h + normie.h) / 2;
    }
    return HSLColor{
        newHue,
        0.5,
        0.5,
    };
}

PopulationVector getNextGeneration(const PopulationVector &population, const SizeTVector &fitnessScore, const SizeTVector &sortedFitnessScoreIndices)
{
    const double ELITE_RATIO = 0.05;
    std::size_t maxEliteIndex = static_cast<std::size_t>(ELITE_RATIO * sortedFitnessScoreIndices.size());

    PopulationVector newPopulation(population.size());
    newPopulation.reserve(population.size());

    // Append elites to population
    for (std::size_t index = 0; index < maxEliteIndex; index++)
    {
        newPopulation.at(index) = (population.at(sortedFitnessScoreIndices.at(index)));
    }

    for (std::size_t index = maxEliteIndex; index < population.size(); ++index)
    {
        const HSLColor elite = population.at(sortedFitnessScoreIndices.at(GenerateRandomValue(0, maxEliteIndex)));

        const HSLColor normie = population.at(sortedFitnessScoreIndices.at(GenerateRandomValue(maxEliteIndex, sortedFitnessScoreIndices.size())));

        const HSLColor child = singlePointCrossOver(elite, normie);

        newPopulation.at(index) = child;
    }

    return newPopulation;
}