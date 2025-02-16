#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image/stb_image.h>

#include <iostream>
#include <string>
#include <thread>

#include "Camera.h"
#include "FMLColor.h"
#include "FMLRenderer.h"
#include "FMLTexture.h"
#include "FMLWindow.h"
#include "Mesh.h"
#include "Model.h"
#include "Rect.h"
#include "Shader.h"
#include "Shape.h"
#include "TexturedQuad.h"
#include "Time.h"

unsigned int loadTexture(std::string fileName);

// settings
unsigned int Screen_width = 800;
unsigned int Screen_height = 600;

// Camera camera;

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

struct RGB
{
    int r, g, b;
};

RGB hueToRGB(float hue)
{
    float s = 1.0f, v = 1.0f; // Assume full saturation and brightness
    float c = s * v;          // Chroma
    float x = c * (1 - fabs(fmod(hue / 60.0, 2) - 1));
    float m = v - c;

    float r, g, b;
    if (hue >= 0 && hue < 60)
    {
        r = c, g = x, b = 0;
    }
    else if (hue < 120)
    {
        r = x, g = c, b = 0;
    }
    else if (hue < 180)
    {
        r = 0, g = c, b = x;
    }
    else if (hue < 240)
    {
        r = 0, g = x, b = c;
    }
    else if (hue < 300)
    {
        r = x, g = 0, b = c;
    }
    else
    {
        r = c, g = 0, b = x;
    }

    return RGB{static_cast<int>((r + m) * 255), static_cast<int>((g + m) * 255), static_cast<int>((b + m) * 255)};
}

int main()
{
    FMLWindow window(Screen_width, Screen_height);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    stbi_set_flip_vertically_on_load(true);

    FMLRenderer renderer(window);
    // FMLTexture matrixTexture("resources/matrix.jpg");
    FMLTexture matrixTexture("resources/DinoSprites.png");

    FML::Time::initialize();
    // render loop
    // -----------
    while (!window.shouldClose())
    {
        FML::Time::update();
        // input
        // -----
        // processInput(window);

        renderer.clear(FMLColor(100, 100, 100));

        // render the triangle
        renderer.drawRect(100, 100, 200, 200, FMLColor(0, 255, 0, 255), true, int(FML::Time::ticks / 10 * 1500) % 360);
        renderer.drawRect(100, 300, 200, 200, FMLColor(0, 0, 255), false, int(FML::Time::ticks / 10 * 1200) % 360);
        renderer.drawRect(300, 100, 200, 200, FMLColor(255, 255, 0), false, int(FML::Time::ticks / 10 * 800) % 360);
        renderer.drawRect(300, 300, 200, 200, FMLColor(255, 0, 255, 150), false, int(FML::Time::ticks / 10 * 500) % 360,
                          Point(0, 0));

        RGB hue = hueToRGB(int(FML::Time::ticks / 10 * 1000) % 360);
        // renderer.drawTexture(matrixTexture, Rect(4, 3, 15, 17), 600, 600, 200, 200,
        //                      int(FML::Time::ticks / 10 * 1000) % 360, FMLColor(hue.r, hue.g, hue.b, 255));
        renderer.drawTexture(matrixTexture, Rect(), 600, 600, 300, 100, false, false,
                             int(FML::Time::ticks / 10 * 1000) % 360, FMLColor(), Point(0, 0));

        renderer.show();
        glfwPollEvents();

        // wait 16ms to simulate 60fps
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    //
    // if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    //     camera.ProcessKeyboard(Camera_Movement::FORWARD, (float)own::Time::deltaTime);
    // if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    //     camera.ProcessKeyboard(Camera_Movement::LEFT, (float)own::Time::deltaTime);
    // if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    //     camera.ProcessKeyboard(Camera_Movement::BACKWARD, (float)own::Time::deltaTime);
    // if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    //     camera.ProcessKeyboard(Camera_Movement::RIGHT, (float)own::Time::deltaTime);
    //
    // if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    //     camera.ProcessKeyboard(Camera_Movement::UP, (float)own::Time::deltaTime);
    // if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    //     camera.ProcessKeyboard(Camera_Movement::DOWN, (float)own::Time::deltaTime);
    //
    // if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    // {
    //     lightPos.x += 1.0f * own::Time::deltaTime;
    // }
    // if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    // {
    //     lightPos.x -= 1.0f * own::Time::deltaTime;
    // }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);

    Screen_width = width;
    Screen_height = height;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    // static float lastX = xpos, lastY = ypos;
    //
    // float xoffset = xpos - lastX;
    // float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
    // lastX = xpos;
    // lastY = ypos;
    //
    // const float sensitivity = 0.1f;
    // xoffset *= sensitivity;
    // yoffset *= sensitivity;
    //
    // camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) { /*  camera.ProcessMouseScroll(yoffset);  */ }

unsigned int loadTexture(std::string filePath)
{

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << filePath << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
