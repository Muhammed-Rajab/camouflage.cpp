#ifndef UI_4_CAMOUFLAGE_H
#define UI_4_CAMOUFLAGE_H

float TextToFloat(const char *text)
{
    return (float)std::atof(text); // Convert the string to a float using standard C function
}

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "raylib.h"
#include "ga.h"

void RenderGUI(GA &ga, float screenWidth, float screenHeight, float renderXPos, float renderYPos, float renderWidth, float renderHeight, float &speedMultiplier, bool &isRunning)
{

    // * ----------------------------------------------------------
    // * WITHIN BOX
    // * ----------------------------------------------------------
    // Rectangle groupBoxBounds{-1, 10, 200, GetMonitorHeight(0) - 20};
    float y = 20.0f;

    // ! SETTINGS LABEL
    GuiLabel({10, y, 100, 20}, "SETTINGS");
    y += 20;

    // ! BORDER CHECK BOX
    (GuiCheckBox({10, y, 20, 20}, "border", &ga.border));
    y += 27;

    // ! PAUSE BTN
    if (GuiButton({10, y, 150, 40}, (isRunning ? "PAUSE" : "RESUME")))
    {
        isRunning = !isRunning;
    };
    y += 45;

    // ! HUE SLIDER
    float hue = ga.BACKGROUND.h;
    GuiLabel({10, y, 100, 20}, "HUE");
    y += 25;
    if (GuiSlider({10, y, 150, 20}, "", TextFormat("%d", ga.BACKGROUND.h), &hue, 0, 360))
    {
        ga.BACKGROUND.h = (int)hue;
    }
    y += 25;

    // ! ELITE RATIO SLIDER
    float elite_ratio = ga.ELITE_RATIO;
    GuiLabel({10, y, 100, 20}, "ELITE RATIO");
    y += 25;
    if (GuiSlider({10, y, 150, 20}, "", TextFormat("%.3f", elite_ratio), &elite_ratio, 0.0005, 1.0))
    {
        ga.ELITE_RATIO = elite_ratio;
    }
    y += 25;

    // ! SPEED MULTIPLIER SLIDER
    GuiLabel({10, y, 150, 20}, "SPEED MULTIPLIER");
    y += 25;
    if (GuiSlider({10, y, 150, 20}, "", TextFormat("%.3f", speedMultiplier), &speedMultiplier, 0.001, 60.0))
    {
        ga.ELITE_RATIO = elite_ratio;
    }
    y += 25;

    // ! STATS
    Stats s = ga.Stat();

    // ! TOP FITNESS
    GuiLabel({10, y, 150, 20}, TextFormat("TOP FITNESS: %d", s.TOP_FITNESS_SCORE));
    y += 25;
    // ! MEDIAN FITNESS
    GuiLabel({10, y, 150, 20}, TextFormat("MEDIAN FITNESS: %d", s.MEDIAN_FITNESS_SCORE));
    y += 25;
    // ! WORST FITNESS
    GuiLabel({10, y, 150, 20}, TextFormat("WORST FITNESS: %d", s.WORST_FITNESS_SCORE));
    y += 25;

    // ! BORDER BOX
    GuiDrawRectangle({-1, 10, 200, y}, 1, WHITE, Color{0, 0, 0, 0});

    // * ----------------------------------------------------------
    // * OUT OF BOX
    // * ----------------------------------------------------------

    // ! MUTATION RATE SLIDER
    float mutation_rate = (float)ga.MUTATION_RATE;
    GuiLabel({renderXPos, renderYPos - 55, 100, 20}, "MUTATION RATE");
    if (GuiSlider({renderXPos - 1, renderYPos - 30, renderWidth + 1, 20}, "", TextFormat("%f", mutation_rate), &mutation_rate, 0.0, 0.5))
    {
        ga.MUTATION_RATE = (double)(mutation_rate);
    }

    // ! GENERATION COUNT LABEL
    GuiLabel({renderXPos + renderWidth - 100, renderYPos - 55, 100, 20}, TextFormat("GENERATION: %ld", ga.GENERATION));
}

#endif