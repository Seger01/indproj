#include "FMLRenderer.h"

#include <glad/glad.h>

#include "GLFW/glfw3.h"

#include "FMLWindow.h"

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image/stb_image.h>

#include <string>

#include "FMLColor.h"
#include "FMLRenderer.h"
#include "FMLTexture.h"
#include "FMLWindow.h"
#include "Rect.h"
#include "Shader.h"

FMLRenderer::FMLRenderer(FMLWindow& window)
    : texturedQuadShader("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl"),
      rectShader("shaders/colored_rect/vertex_shader.glsl", "shaders/colored_rect/fragment_shader.glsl"), window(window)
{
    texturedQuadShader.use();
    texturedQuadShader.setInt("texture1", 0);

    glDisable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void FMLRenderer::clear(const FMLColor& color)
{
    glClearColor(color.normalize().r, color.normalize().g, color.normalize().b, color.normalize().a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void FMLRenderer::show() { glfwSwapBuffers(window.getWindow()); }

void FMLRenderer::drawTexture(const FMLTexture& texture, const Rect& source, int x, int y, int width, int height,
                              float rotation)
{
    texturedQuad.bindVAO();

    Point windowSize = window.getWindowSize();

    texturedQuadShader.use();
    texturedQuadShader.setInt("texture1", 0);

    glm::mat4 projection = glm::ortho(0.0f, (float)windowSize.x, (float)windowSize.y, 0.0f, -1.0f, 1.0f);
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, glm::vec3(x, y, 0.0f));
    model = glm::rotate(model, glm::radians((float)rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(width, height, 1.0f));

    texturedQuadShader.setMat4("model", model);
    texturedQuadShader.setMat4("projection", projection);

    if (source.w == 0 && source.h == 0)
    {
        texturedQuadShader.setVec4("source", glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
    }
    else
    {
        texturedQuadShader.setVec4(
            "source", glm::vec4(((float)source.x) / texture.getSize().x, ((float)source.y - 1) / texture.getSize().y,
                                (float)source.w / texture.getSize().x, (float)source.h / texture.getSize().y));
    }

    texture.activate();

    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void FMLRenderer::drawRect(int x, int y, int width, int height, const FMLColor& color, float rotation)
{
    texturedQuad.bindVAO();

    Point windowSize = window.getWindowSize();

    rectShader.use();

    glm::mat4 projection = glm::ortho(0.0f, (float)windowSize.x, (float)windowSize.y, 0.0f, -1.0f, 1.0f);
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, glm::vec3(x, y, 0.0f));
    model = glm::rotate(model, glm::radians((float)rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(width, height, 1.0f));

    rectShader.setMat4("model", model);
    rectShader.setMat4("projection", projection);

    rectShader.setVec4("color",
                       glm::vec4(color.normalize().r, color.normalize().g, color.normalize().b, color.normalize().a));

    glDrawArrays(GL_TRIANGLES, 0, 6);
}
