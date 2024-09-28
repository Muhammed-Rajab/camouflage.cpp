#include "raylib.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "hsl.h"

int GenerateRandomValue(int min, int max)
{
    return min + rand() % (max - min + 1);
}

int main()
{

    // ! RANDOM GENERATOR SEEDING
    srand(time(NULL));

    // ! WINDOW PROPERTIES
    const int screenWidth = 600;
    const int screenHeight = 600;
    const char *title = "Camouflage";

    // ! RAYLIB SETUP
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_BORDERLESS_WINDOWED_MODE);
    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(screenWidth, screenHeight, title);
    SetTargetFPS(60);

    // ! ALGO SETUP
    const int COL_COUNT = 10;
    const int ROW_COUNT = 10;

    const int PADDING_X = 30;
    const int PADDING_Y = 30;

    const int OFFSET_X = PADDING_X;
    const int OFFSET_Y = PADDING_Y;

    const int GRID_WIDTH = (screenWidth - 2 * PADDING_X) / COL_COUNT;
    const int GRID_HEIGHT = (screenHeight - 2 * PADDING_Y) / ROW_COUNT;

    const Color BACKGROUND = {0, 255, 60};

    std::size_t VECTOR_SIZE = COL_COUNT * ROW_COUNT * 3;
    std::vector<int> population(VECTOR_SIZE);

    for (std::size_t index = 0; index < VECTOR_SIZE; ++index)
    {
        population.at(index) = GenerateRandomValue(0, 255);
    }

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BACKGROUND);

        // * YOU DRAWING STARTS HERE ------------>

        // ! GOES THROUGH EVERY CELL
        std::size_t pos = 0;
        for (std::size_t row = 0; row < ROW_COUNT; ++row)
        {
            const int y = row * GRID_HEIGHT + OFFSET_Y;
            for (std::size_t col = 0; col < COL_COUNT; ++col)
            {
                const int x = col * GRID_WIDTH + OFFSET_X;
                const int index = (COL_COUNT * row + col) * 3;

                unsigned char r = population.at(index);
                unsigned char g = population.at(index + 1);
                unsigned char b = population.at(index + 2);

                DrawRectangle(x, y, GRID_WIDTH, GRID_HEIGHT, Color{r, g, b, 255});

                pos += 3;
            }
        }
        DrawFPS(10, 10);
        EndDrawing();

        // break;
    }

    CloseWindow();

    return 0;
}