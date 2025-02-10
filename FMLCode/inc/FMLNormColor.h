#pragma once

class FMLColor;

class FMLNormColor
{
public:
    FMLNormColor();

    FMLNormColor(float r, float g, float b);

    FMLNormColor(float r, float g, float b, float a);

    FMLColor denormalize() const;

    float r, g, b, a;
};
