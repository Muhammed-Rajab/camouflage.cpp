#include "raylib.h"
#include <iostream>
#include <sstream>
#include <vector>

#include "ga.h"
#include "hsl.h"
#include "ui.h"

int main()
{

    // ! RANDOM GENERATOR SEEDING
    srand(time(NULL));

    // ! WINDOW PROPERTIES
    // const int screenWidth = 800;
    // const int screenHeight = 800;
    const char *title = "Camouflage";

    // ! RAYLIB SETUP
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_BORDERLESS_WINDOWED_MODE);
    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(800, 800, title);
    SetTargetFPS(12);

    const int screenWidth = GetMonitorWidth(0);
    const int screenHeight = GetMonitorHeight(0);
    SetWindowSize(screenWidth, screenHeight);
    ToggleFullscreen();

    // ! GUI SETUP
    GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, ColorToInt(WHITE));

    // ! ALGO SETUP
    const int COL_COUNT = 10;
    const int ROW_COUNT = 10;

    HSLColor BACKGROUND_HSL = {31, 0.5, 0.5};

    GA ga(ROW_COUNT, COL_COUNT, 0.0005, BACKGROUND_HSL);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(HSLToColor(ga.BACKGROUND));

        // * YOU DRAWING STARTS HERE ------------>
        ga.Render((screenWidth / 2) - 300, (screenHeight / 2) - 300, 600, 600);
        ga.Update();

        RenderGUI(ga, screenWidth, screenHeight, (screenWidth / 2) - 300, (screenHeight / 2) - 300, 600, 600);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
