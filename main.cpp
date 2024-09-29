#include "raylib.h"
#include <iostream>
#include <vector>

#include "ga.h"
#include "hsl.h"

int main()
{

    // ! RANDOM GENERATOR SEEDING
    srand(time(NULL));

    // ! WINDOW PROPERTIES
    const int screenWidth = 500;
    const int screenHeight = 500;
    const char *title = "Camouflage";

    // ! RAYLIB SETUP
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_BORDERLESS_WINDOWED_MODE);
    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(screenWidth, screenHeight, title);
    // SetTargetFPS(60);

    // ! ALGO SETUP
    const int COL_COUNT = 75;
    const int ROW_COUNT = 75;

    const int PADDING_X = 25;
    const int PADDING_Y = 25;

    const int OFFSET_X = PADDING_X;
    const int OFFSET_Y = PADDING_Y;

    const int GRID_WIDTH = (screenWidth - 2 * PADDING_X) / COL_COUNT;
    const int GRID_HEIGHT = (screenHeight - 2 * PADDING_Y) / ROW_COUNT;

    const HSLColor BACKGROUND_HSL = {120, 0.5, 0.5};
    const RGBColor BACKGROUND_RGB = HSLToRGB(BACKGROUND_HSL.h, BACKGROUND_HSL.s, BACKGROUND_HSL.l);
    const Color BACKGROUND = {(unsigned char)BACKGROUND_RGB.r, (unsigned char)BACKGROUND_RGB.g, (unsigned char)BACKGROUND_RGB.b};

    const std::size_t POPULATION_SIZE = COL_COUNT * ROW_COUNT;

    PopulationVector population = generateRandomPopulation(POPULATION_SIZE);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BACKGROUND);

        // * YOU DRAWING STARTS HERE ------------>

        // ! RENDER POPULATION
        renderPopulation(population, GRID_WIDTH, GRID_HEIGHT, ROW_COUNT, COL_COUNT, OFFSET_X, OFFSET_Y);

        // ! CALCULATE POPULATION FITNESS
        SizeTVector fitnessScore = calculatePopulationFitness(population, BACKGROUND_HSL);

        // ! GET SORTED FITNESS
        SizeTVector sortedFitnessScoreIndices = getSortedFitnessScoresIndices(fitnessScore);

        // ! GENERATE NEXT POPULATION FROM CURRENT POPULATION, SORTED FITNESS SCORE INDICES, AND FITNESS SCORES.
        // population = getNextGeneration(population, fitnessScore, sortedFitnessScoreIndices);

        DrawFPS(10, 10);
        EndDrawing();

        // break;
    }

    CloseWindow();

    return 0;
}
