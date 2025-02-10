#include "FMLNormColor.h"

#include "FMLColor.h"

FMLNormColor::FMLNormColor() : r(0), g(0), b(0), a(0) {}

FMLNormColor::FMLNormColor(float r, float g, float b) : r(r), g(g), b(b), a(1) {}

FMLNormColor::FMLNormColor(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

FMLColor FMLNormColor::denormalize() const { return FMLColor(r * 255, g * 255, b * 255, a * 255); }
