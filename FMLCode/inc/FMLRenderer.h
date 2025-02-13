#pragma once

#include "TexturedQuad.h"
#include "glad/glad.h"

#include "FMLColor.h"
#include "FMLTexture.h"
#include "Shader.h"

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
                     float rotation = 0.0f);
    void drawRect(int x, int y, int width, int height, const FMLColor& color, float rotation = 0.0f);

private:
    FMLWindow& window;

    Shader texturedQuadShader;
    Shader rectShader;

    TexturedQuad texturedQuad;
};
