#pragma once

#include "Vector2.h"
#include <string>

class FMLTexture
{
public:
    FMLTexture(const std::string& filePath);
    virtual ~FMLTexture() = default;

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
