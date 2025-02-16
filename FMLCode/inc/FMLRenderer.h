#pragma once

#include "glad/glad.h"

#include "FMLColor.h"
#include "FMLTexture.h"
#include "Point.h"
#include "Shader.h"
#include "TexturedQuad.h"
#include "UnfilledBox.h"

class FMLWindow;
class Rect;

class FMLRenderer
{
public:
    FMLRenderer(FMLWindow& window);
    virtual ~FMLRenderer() = default;

    void clear(const FMLColor& color);
    void show();

    void drawTexture(const FMLTexture& texture, const Rect& source, int x, int y, int width, int height,
                     bool flipX = false, bool flipY = false, float rotation = 0.0f,
                     const FMLColor& colorFilter = FMLColor(255, 255, 255, 255),
                     const Point& rotationalCenter = Point(INT_MAX, INT_MAX));
    void drawRect(int x, int y, int width, int height, const FMLColor& color, bool fill = true, float rotation = 0.0f,
                  const Point& rotationalCenter = Point(INT_MAX, INT_MAX));

private:
    FMLWindow& window;

    Shader texturedQuadShader;
    Shader rectShader;

    TexturedQuad texturedQuad;
    UnfilledBox unfilledBox;
};
