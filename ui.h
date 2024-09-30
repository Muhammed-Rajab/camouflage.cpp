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

void RenderGUI(GA &ga, float screenWidth, float screenHeight, float renderXPos, float renderYPos, float renderWidth, float renderHeight, float &speedMultiplier)
{

    // * ----------------------------------------------------------
    // * WITHIN BOX
    // * ----------------------------------------------------------
    // Rectangle groupBoxBounds{-1, 10, 200, GetMonitorHeight(0) - 20};
    Rectangle groupBoxBounds{-1, 10, 200, 280};

    // ! BORDER BOX
    GuiDrawRectangle(groupBoxBounds, 1, WHITE, Color{0, 0, 0, 0});

    // ! SETTINGS LABEL
    GuiLabel({10, 20, 100, 20}, "PROPERTIES");

    // ! CHECK BOX
    (GuiCheckBox({10, 40, 20, 20}, "border", &ga.border));

    // ! HUE SLIDER
    float hue = ga.BACKGROUND.h;
    GuiLabel({10, 65, 100, 20}, "HUE");
    if (GuiSlider({10, 85, 150, 20}, "", TextFormat("%d", ga.BACKGROUND.h), &hue, 0, 360))
    {
        ga.BACKGROUND.h = (int)hue;
    }

    // ! ELITE RATIO SLIDER
    float elite_ratio = ga.ELITE_RATIO;
    GuiLabel({10, 110, 100, 20}, "ELITE RATIO");
    if (GuiSlider({10, 135, 150, 20}, "", TextFormat("%.3f", elite_ratio), &elite_ratio, 0.0005, 1.0))
    {
        ga.ELITE_RATIO = elite_ratio;
    }

    // ! SPEED MULTIPLIER SLIDER
    GuiLabel({10, 160, 100, 20}, "SPEED MULTIPLIER");
    if (GuiSlider({10, 185, 150, 20}, "", TextFormat("%.3f", speedMultiplier), &speedMultiplier, 0.001, 60.0))
    {
        ga.ELITE_RATIO = elite_ratio;
    }

    // ! STATS
    Stats s = ga.Stat();

    // ! TOP FITNESS
    GuiLabel({10, 210, 150, 20}, TextFormat("TOP FITNESS: %d", s.TOP_FITNESS_SCORE));
    // ! MEDIAN FITNESS
    GuiLabel({10, 235, 150, 20}, TextFormat("MEDIAN FITNESS: %d", s.MEDIAN_FITNESS_SCORE));
    // ! WORST FITNESS
    GuiLabel({10, 260, 150, 20}, TextFormat("WORST FITNESS: %d", s.WORST_FITNESS_SCORE));

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