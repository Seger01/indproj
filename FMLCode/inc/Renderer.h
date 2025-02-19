#pragma once

#include "glad/glad.h"

#include "Color.h"
#include "Point.h"
#include "Shader.h"
#include "Texture.h"
#include "TexturedQuad.h"
#include "UnfilledBox.h"

namespace FML
{

class Window;
class Rect;

class Renderer
{
public:
    Renderer(Window& window);
    virtual ~Renderer() = default;

    void clear(const Color& color);
    void show();

    void drawTexture(const Texture& texture, const Rect& source, int x, int y, int width, int height,
                     bool flipX = false, bool flipY = false, float rotation = 0.0f,
                     const Color& colorFilter = Color(255, 255, 255, 255),
                     const Point& rotationalCenter = Point(INT_MAX, INT_MAX));
    void drawRect(int x, int y, int width, int height, const Color& color, bool fill = true, float rotation = 0.0f,
                  const Point& rotationalCenter = Point(INT_MAX, INT_MAX));
    void drawCircle(int x, int y, int radius, const Color& color, bool fill = true, int lineWidth = 1);

    void setViewport(const Rect& rect);

    Rect getViewport();
    Point getViewportSize();

private:
    Window& window;

    Shader texturedQuadShader;
    Shader rectShader;
    Shader circleShader;

    TexturedQuad texturedQuad;
    UnfilledBox unfilledBox;
};

} // namespace FML
