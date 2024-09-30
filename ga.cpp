#include <vector>
#include <iostream>

#include "hsl.h"
#include "algos.h"
#include "raylib.h"
#include "ga.h"

// *--------------------------------------------
// * GA CLASS IMPLEMENTATION
// *--------------------------------------------

// ! CONSTRUCTORS
GA::GA(std::size_t row_count, std::size_t col_count, double mutation_rate, HSLColor background)
{
    this->ROW_COUNT = row_count;
    this->COL_COUNT = col_count;
    this->BACKGROUND = background;
    this->MUTATION_RATE = mutation_rate;
    this->POPULATION_SIZE = row_count * col_count;

    // ! INITIALIZE THE VECTORS
    this->population = PopulationVector(this->POPULATION_SIZE);
    this->fitnessScores = SizeTVector(this->POPULATION_SIZE);
    this->sortedFitnessScoresIndices = SizeTVector(this->POPULATION_SIZE);

    // ! INITIALIZE RANDOM POPULATION
    this->generateRandomPopulation();
}

// ! GENERATION
void GA::generateRandomPopulation()
{
    std::vector<HSLColor> population(this->POPULATION_SIZE);

    for (std::size_t index = 0; index < this->POPULATION_SIZE; ++index)
    {
        // ! POPULATION WILL HAVE DIFFERENT HUE ONLY
        // ! BUT SAME SATURATION AND LIGHTNESS, TO KEEP THINGS SIMPLE
        population.at(index) = HSLColor{
            GenerateRandomValue(0, 360),
            0.5,
            0.5,
        };
    }

    this->population = population;
}

// ! FITNESS CALCULATION
int GA::calculateHueDifference(int h1, int h2)
{
    int deltaH = std::abs(h1 - h2);
    return std::min(deltaH, 360 - deltaH);
}

void GA::calculatePopulationFitness()
{
    SizeTVector fitnessScores;
    fitnessScores.reserve(population.size());

    for (const HSLColor &individual : population)
    {
        fitnessScores.push_back(360 - calculateHueDifference(this->BACKGROUND.h, individual.h));
    }

    this->fitnessScores = fitnessScores;
}

void GA::calculateSortedFitnessScoresIndices()
{
    this->sortedFitnessScoresIndices = argsort(this->fitnessScores);
}

// ! CROSSOVER
HSLColor GA::breed(const HSLColor &elite, const HSLColor &normie, const std::size_t eliteFitnessScore, const std::size_t normieFitnessScore)
{
    double totalFitness = eliteFitnessScore + normieFitnessScore;
    double w1 = eliteFitnessScore / totalFitness;
    double w2 = normieFitnessScore / totalFitness;

    int newHue = (elite.h * w1 + normie.h * w2);

    if (rand() % 100 < this->MUTATION_RATE * 100)
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

void GA::getNextGeneration()
{
    std::size_t maxEliteIndex = static_cast<std::size_t>(this->ELITE_RATIO * this->sortedFitnessScoresIndices.size());

    PopulationVector newPopulation(population.size());

    // ! ADDING ELITES TO THE NEW POPULATION
    for (std::size_t index = 0; index < maxEliteIndex; ++index)
    {
        newPopulation.at(index) = (this->population.at(this->sortedFitnessScoresIndices.at(index)));
    }

    for (std::size_t index = maxEliteIndex; index < population.size(); ++index)
    {
        const std::size_t eliteIndex = GenerateRandomValue(0, maxEliteIndex - 1);
        const std::size_t normieIndex = GenerateRandomValue(maxEliteIndex, this->sortedFitnessScoresIndices.size() - 1);

        const HSLColor elite = population.at(this->sortedFitnessScoresIndices.at(eliteIndex));
        const HSLColor normie = population.at(this->sortedFitnessScoresIndices.at(normieIndex));

        const std::size_t eliteFitnessScore = this->fitnessScores.at(this->sortedFitnessScoresIndices.at(eliteIndex));
        const std::size_t normieFitnessScore = this->fitnessScores.at(this->sortedFitnessScoresIndices.at(normieIndex));

        const HSLColor child = this->breed(elite, normie, eliteFitnessScore, normieFitnessScore);
        newPopulation.at(index) = child;
    }

    this->population = newPopulation;
}

// ! RENDERING
void GA::Update()
{
    this->calculatePopulationFitness();
    this->calculateSortedFitnessScoresIndices();
    this->getNextGeneration();

    ++this->GENERATION;
}

void GA::Render(int xPos, int yPos, int width, int height)
{
    std::size_t pos = 0;

    const std::size_t GRID_WIDTH = width / this->COL_COUNT;
    const std::size_t GRID_HEIGHT = height / this->ROW_COUNT;

    for (std::size_t row = 0; row < this->ROW_COUNT; ++row)
    {
        const int y = row * GRID_HEIGHT + yPos;
        for (std::size_t col = 0; col < this->COL_COUNT; ++col)
        {
            const int x = col * GRID_WIDTH + xPos;
            const int index = (this->COL_COUNT * row + col);

            const HSLColor &hsl = this->population.at(index);
            const RGBColor &rgb = HSLToRGB(hsl.h, hsl.s, hsl.l);

            DrawRectangle(x, y, GRID_WIDTH, GRID_HEIGHT, Color{(unsigned char)rgb.r, (unsigned char)rgb.g, (unsigned char)rgb.b, 255});

            pos += 3;
        }
    }

    if (this->border)
    {
        DrawRectangleLinesEx(Rectangle{(float)xPos - 4, (float)yPos - 4, (float)GRID_WIDTH * this->COL_COUNT + 4, (float)GRID_HEIGHT * this->ROW_COUNT + 4}, 4, WHITE);
    }
}

// ! STATS
Stats GA::Stat()
{
    Stats s;
    s.BACKGROUND = this->BACKGROUND;
    s.GENERATION = this->GENERATION;
    s.ELITE_RATIO = this->ELITE_RATIO;
    s.MUTATION_RATE = this->MUTATION_RATE;

    s.TOP_FITNESS_SCORE = this->fitnessScores.at(this->sortedFitnessScoresIndices.at(0));
    s.MEDIAN_FITNESS_SCORE = this->fitnessScores.at(this->sortedFitnessScoresIndices.at(this->sortedFitnessScoresIndices.size() / 2));
    s.WORST_FITNESS_SCORE = this->fitnessScores.at(this->sortedFitnessScoresIndices.at(this->sortedFitnessScoresIndices.size() - 1));

    return s;
}

void GA::SetBackgroundHue(int hue)
{
    this->BACKGROUND.h = hue;
}