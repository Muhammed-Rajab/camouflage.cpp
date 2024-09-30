#include "raylib.h"
#include <iostream>
#include <sstream>
#include <vector>

#include "ga.h"
#include "hsl.h"

float TextToFloat(const char *text)
{
    return (float)std::atof(text); // Convert the string to a float using standard C function
}

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

int main()
{

    // ! RANDOM GENERATOR SEEDING
    srand(time(NULL));

    // ! WINDOW PROPERTIES
    const int screenWidth = 800;
    const int screenHeight = 800;
    const char *title = "Camouflage";

    // ! RAYLIB SETUP
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_BORDERLESS_WINDOWED_MODE);
    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(screenWidth, screenHeight, title);
    SetTargetFPS(12);

    // ! ALGO SETUP
    std::size_t generation = 0;

    const int COL_COUNT = 10;
    const int ROW_COUNT = 10;

    const int PADDING_X = 25;
    const int PADDING_Y = 25;

    const int OFFSET_X = PADDING_X;
    const int OFFSET_Y = PADDING_Y;

    const int GRID_WIDTH = (screenWidth - 2 * PADDING_X) / COL_COUNT;
    const int GRID_HEIGHT = (screenHeight - 2 * PADDING_Y) / ROW_COUNT;

    const std::size_t POPULATION_SIZE = COL_COUNT * ROW_COUNT;

    PopulationVector population = generateRandomPopulation(POPULATION_SIZE);

    float bgHue = 0.0f;

    while (!WindowShouldClose())
    {
        // ! CALCULATING THE BACKGROUND
        Vector2 mPos = GetMousePosition();
        // HSLColor BACKGROUND_HSL = {(int)((int)mPos.x % 360), 0.5, 0.5};
        HSLColor BACKGROUND_HSL = {bgHue, 0.5, 0.5};
        RGBColor BACKGROUND_RGB = HSLToRGB(BACKGROUND_HSL.h, BACKGROUND_HSL.s, BACKGROUND_HSL.l);
        Color BACKGROUND = {(unsigned char)BACKGROUND_RGB.r, (unsigned char)BACKGROUND_RGB.g, (unsigned char)BACKGROUND_RGB.b};

        BeginDrawing();
        ClearBackground(BACKGROUND);

        // * YOU DRAWING STARTS HERE ------------>

        // if (GuiButton((Rectangle){24, 24, 120, 30}, "#191#Show Message"))
        //     std::cout << "hi\n";
        GuiSlider(Rectangle{10, 10, 600, 20}, "Test", "Hello", &bgHue, 0.0f, 360.0f);

        // ! RENDER POPULATION
        renderPopulation(population, (screenWidth / 2) - 300, (screenHeight / 2) - 300, 600, 600, ROW_COUNT, COL_COUNT, true);

        // ! CALCULATE POPULATION FITNESS
        SizeTVector fitnessScore = calculatePopulationFitness(population, BACKGROUND_HSL);

        // ! GET SORTED FITNESS
        SizeTVector sortedFitnessScoreIndices = getSortedFitnessScoresIndices(fitnessScore);

        // ! RENDER STATS
        std::ostringstream oss;
        oss << "GEN: " << generation << "\n\n";
        oss << "TOP FITNESS: " << fitnessScore.at(sortedFitnessScoreIndices.at(0)) << "\n\n";
        oss << "MEDIAN FITNESS: " << fitnessScore.at(sortedFitnessScoreIndices.at(sortedFitnessScoreIndices.size() / 2)) << "\n\n";
        oss << "WORST FITNESS: " << fitnessScore.at(sortedFitnessScoreIndices.at(sortedFitnessScoreIndices.size() - 1)) << "\n";
        DrawText(oss.str().c_str(), 10, 10, 20, WHITE);

        // ! GENERATE NEXT POPULATION FROM CURRENT POPULATION, SORTED FITNESS SCORE INDICES, AND FITNESS SCORES.
        population = getNextGeneration(population, fitnessScore, sortedFitnessScoreIndices);

        // DrawFPS(10, 10);
        EndDrawing();

        // break;
        ++generation;
    }

    CloseWindow();

    return 0;
}
