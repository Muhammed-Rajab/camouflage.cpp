#ifndef HSL_4_CAMOUFLAGE_H
#define HSL_4_CAMOUFLAGE_H

#include <cmath>

struct HSLColor
{
    int h;
    float s;
    float l;
};

struct RGBColor
{
    int r;
    int g;
    int b;
};

RGBColor HSLToRGB(int h, float s, float l)
{
    float c = (1 - std::fabs(2 * l - 1)) * s;

    float x = c * (1 - fabs(fmod(h / 60.0f, 2) - 1));

    float R1, G1, B1;

    if (h >= 0 && h < 60)
    {
        R1 = c;
        G1 = x;
        B1 = 0;
    }
    else if (h >= 60 && h < 120)
    {
        R1 = x;
        G1 = c;
        B1 = 0;
    }
    else if (h >= 120 && h < 180)
    {
        R1 = 0;
        G1 = c;
        B1 = x;
    }
    else if (h >= 180 && h < 240)
    {
        R1 = 0;
        G1 = x;
        B1 = c;
    }
    else if (h >= 240 && h < 300)
    {
        R1 = x;
        G1 = 0;
        B1 = c;
    }
    else if (h >= 300 && h < 360)
    {
        R1 = c;
        G1 = 0;
        B1 = x;
    }

    const float m = l - (c / 2);
    return RGBColor{
        static_cast<int>(round((R1 + m) * 255)),
        static_cast<int>(round((G1 + m) * 255)),
        static_cast<int>(round((B1 + m) * 255)),
    };
}
#endif