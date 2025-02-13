#include "TexturedQuad.h"

// define vertices for a triangle
std::vector<float> vertices = {
    // positions // texture coords
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
    -0.5f, 0.5f,  0.0f, 0.0f, 1.0f, // top left
    0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // top right

    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
    0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // top right
    0.5f,  -0.5f, 0.0f, 1.0f, 0.0f  // bottom right
};

TexturedQuad::TexturedQuad() : Shape(vertices) {}
