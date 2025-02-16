#pragma once

#include <vector>

class Shape
{
public:
    Shape();
    Shape(std::vector<float> vertices);
    virtual ~Shape() = default;

    void loadVertices(std::vector<float> vertices);

    void bindVAO();

protected:
    unsigned int VBO, VAO;
};
