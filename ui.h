#ifndef UI_4_CAMOUFLAGE_H
#define UI_4_CAMOUFLAGE_H

float TextToFloat(const char *text)
{
    return (float)std::atof(text); // Convert the string to a float using standard C function
}

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "ga.h"

void RenderGUI(GA &ga)
{
    // ! TURN ON/OFF BORDER
    if (GuiCheckBox({100, 100, 20, 20}, "border", &ga.border))
    {
        std::cout << "Border: " << (ga.border ? "ON" : "OFF") << "\n";
    }

    // ! CHANGE BACKGROUND HUE
    float hue = ga.BACKGROUND.h;
    if (GuiSlider({100, 120, 100, 20}, "", "hue", &hue, 0, 360))
    {
        ga.BACKGROUND.h = (int)hue;
    }
}

#endif