#pragma once

#include "Vector2.h"
#include <string>

namespace FML
{

class Texture
{
public:
    Texture(const std::string& filePath);
    virtual ~Texture() = default;

    void activate() const;

    unsigned int getTextureID() const;
    Vector2 getSize() const;

private:
    void loadTexture();

private:
    unsigned int mTextureID;

    std::string mFilePath;
    Vector2 mSize;
};

} // namespace FML
