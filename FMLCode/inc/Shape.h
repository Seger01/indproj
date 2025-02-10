#pragma once

#include <vector>

class Shape
{
public:
    Shape(std::vector<float> vertices);
    virtual ~Shape() = default;

    void bindVAO();

protected:
    unsigned int VBO, VAO;
};
