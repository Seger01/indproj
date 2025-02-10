#include "FMLRenderer.h"

#include <glad/glad.h>

FMLRenderer::FMLRenderer(GLFWwindow* window)
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

void FMLRenderer::show() { glfwSwapBuffers(window); }

void FMLRenderer::renderTexture(const FMLTexture& texture)
{
    standardShader.use();
    standardShader.setInt("texture1", 0);

    // activate texture
    texture.activate();

    // render the triangle
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
