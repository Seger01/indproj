#pragma once

#include "FMLColor.h"
#include "FMLTexture.h"
#include "GLFW/glfw3.h"

#include "Point.h"
#include "Vector2.h"

class FMLWindow
{
public:
    FMLWindow(int width, int height);
    virtual ~FMLWindow() = default;

    void clear(const FMLColor& color);
    void show();

    Point getWindowSize();

    bool shouldClose();

    GLFWwindow* getWindow() { return window; }

private:
    // static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    GLFWwindow* window;

    int mScreenWidth, mScreenHeight;
};
