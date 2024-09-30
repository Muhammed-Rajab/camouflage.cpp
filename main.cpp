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
    const int COL_COUNT = 10;
    const int ROW_COUNT = 10;

    HSLColor BACKGROUND_HSL = {31, 0.5, 0.5};
    RGBColor BACKGROUND_RGB = HSLToRGB(BACKGROUND_HSL.h, BACKGROUND_HSL.s, BACKGROUND_HSL.l);
    Color BACKGROUND = {(unsigned char)BACKGROUND_RGB.r, (unsigned char)BACKGROUND_RGB.g, (unsigned char)BACKGROUND_RGB.b};

    GA ga(ROW_COUNT, COL_COUNT, 0.0005, BACKGROUND_HSL);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BACKGROUND);

        // * YOU DRAWING STARTS HERE ------------>
        ga.Render((screenWidth / 2) - 300, (screenHeight / 2) - 300, 600, 600);
        ga.Update();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
