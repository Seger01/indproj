#include "FMLRenderer.h"

#include <glad/glad.h>

#include "GLFW/glfw3.h"

#include "FMLWindow.h"

FMLRenderer::FMLRenderer(FMLWindow& window)
    : standardShader("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl"), window(window)
{
    standardShader.use();
    standardShader.setInt("texture1", 0);

    glEnable(GL_DEPTH_TEST);
}

void FMLRenderer::clear(const FMLColor& color)
{
    glClearColor(color.normalize().r, color.normalize().g, color.normalize().b, color.normalize().a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void FMLRenderer::show() { glfwSwapBuffers(window.getWindow()); }

void FMLRenderer::renderTexture(const FMLTexture& texture, int x, int y, int width, int height)
{
    Point windowSize = window.getWindowSize();

    standardShader.use();
    standardShader.setInt("texture1", 0);

    standardShader.setInt("screenSize.x", windowSize.x);
    standardShader.setInt("screenSize.y", windowSize.y);

    standardShader.setInt("objectPosition.x", x);
    standardShader.setInt("objectPosition.y", y);

    standardShader.setInt("objectSize.x", width);
    standardShader.setInt("objectSize.y", height);

    standardShader.setInt("objectCenter.x", x + width / 2);
    standardShader.setInt("objectCenter.y", y + height / 2);

    // activate texture
    texture.activate();

    // render the triangle
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
