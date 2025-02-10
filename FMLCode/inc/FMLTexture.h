#pragma once

#include <string>

class FMLTexture
{
public:
    FMLTexture(const std::string& filePath);
    virtual ~FMLTexture() = default;

    void activate() const;

    unsigned int getTextureID() const;

private:
    void loadTexture();

private:
    unsigned int mTextureID;

    std::string mFilePath;
};
