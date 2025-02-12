#pragma once

#include "glad/glad.h"

#include "FMLColor.h"
#include "FMLTexture.h"
#include "Shader.h"

class FMLWindow;

class FMLRenderer
{
public:
    FMLRenderer(FMLWindow& window);
    virtual ~FMLRenderer() = default;

    void clear(const FMLColor& color);
    void show();

    void renderTexture(const FMLTexture& texture, int x, int y, int width, int height);

private:
    FMLWindow& window;

    Shader standardShader;
};
