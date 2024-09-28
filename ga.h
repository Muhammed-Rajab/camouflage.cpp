#ifndef GA_4_CAMOUFLAGE_H
#define GA_4_CAMOUFLAGE_H

#include <vector>
#include <iostream>

#include "hsl.h"
#include "algos.h"
#include "raylib.h"

using PopulationVector = std::vector<HSLColor>;
using SizeTVector = std::vector<std::size_t>;

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

#endif