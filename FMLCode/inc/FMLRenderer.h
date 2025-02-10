#pragma once

#include "glad/glad.h"

#include "GLFW/glfw3.h"

#include "FMLColor.h"
#include "FMLTexture.h"
#include "Shader.h"

class FMLRenderer
{
public:
    FMLRenderer(GLFWwindow* window);
    virtual ~FMLRenderer() = default;

    void clear(const FMLColor& color);
    void show();

    void renderTexture(const FMLTexture& texture);

private:
    GLFWwindow* window;

    Shader standardShader;
};
