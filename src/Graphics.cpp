#if defined(__linux__) || defined(__APPLE__)
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_ttf.h>
#elif defined(_WIN32)
    #include <SDL.h>
    #include <SDL_image.h>
    #include <SDL_ttf.h>
#endif

#include <stdexcept>
#include <iostream>
#include "Graphics.hpp"
#include "Pair.hpp"

Graphics::Graphics()
        : _window("", 800, 600),
          _renderer(_window.getSDLWindowObject()),
          _textureLoader("textures"),
          _fontLoader("fonts")
{
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
    {
        throw runtime_error("Couldn't initialize SDL video subsystem.");
    }

    if (TTF_Init() < 0)
    {
        throw runtime_error("Couldn't initialize SDL TTF.");
    }
}

Graphics::~Graphics()
{
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    TTF_Quit();
}

void Graphics::drawPoint(const Colour& colour, const int x, const int y)
{
    Pair<int, int> adjustedPoint(x, y);
    _cameras.adjustPosition(adjustedPoint);
    
    _renderer.setDrawColour(colour);
    SDL_RenderDrawPoint(_renderer.getSDLRendererObject(), adjustedPoint.first, adjustedPoint.second);
}

void Graphics::drawPoint(const Colour& colour, const Pair<int, int>& point)
{
    drawPoint(colour, point.first, point.second);
}

void Graphics::drawLine(const Colour& colour, const int x0, const int y0, const int x1, const int y1)
{
    Pair<int, int> adjustedStart(x0, y0);
    Pair<int, int> adjustedEnd(x1, y1);
    _cameras.adjustPosition(adjustedStart);
    _cameras.adjustPosition(adjustedEnd);

    _renderer.setDrawColour(colour);
    SDL_RenderDrawLine(_renderer.getSDLRendererObject(), adjustedStart.first, adjustedStart.second, adjustedEnd.first, adjustedEnd.second);
}

void Graphics::drawLine(const Colour& colour, const Pair<int, int>& start, const Pair<int, int>& end)
{
    drawLine(colour, start.first, start.second, end.first, end.second);
}

void Graphics::drawRectangle(const Colour& colour, bool fill, const int x, const int y, const int width, const int height)
{
    Pair<int, int> adjustedOrigin(x, y);
    _cameras.adjustPosition(adjustedOrigin);
    SDL_Rect newRect = { adjustedOrigin.first, adjustedOrigin.second, width, height };

    _renderer.setDrawColour(colour);
    if (fill)
    {
        SDL_RenderFillRect(_renderer.getSDLRendererObject(), &newRect);
    }
    else
    {
        SDL_RenderDrawRect(_renderer.getSDLRendererObject(), &newRect);
    }
}

void Graphics::drawRectangle(const Colour& colour, bool fill, const Pair<int, int>& origin, const Pair<int, int>& opposite)
{
    drawRectangle(colour, fill, origin.first, origin.second, opposite.first, opposite.second);
}

void Graphics::drawRectangle(const Colour& colour, bool fill, const Rectangle& rectangle)
{
    drawRectangle(colour, fill, rectangle.x, rectangle.y, rectangle.width, rectangle.height);
}

Texture& Graphics::getTexture(string filename)
{
    return _textureLoader.get(filename);
}

void Graphics::drawTexture(string filename, const TextureDrawData& data)
{
    SDL_Rect srcRect;
    SDL_Rect *p_srcRect;
    if (data.sourceRectangle == nullptr)
    {
        p_srcRect = NULL;
    }
    else
    {
        srcRect = data.sourceRectangle->toSDLRect();
        p_srcRect = &srcRect;
    }

    SDL_Rect destRect;
    SDL_Rect *p_destRect;
    if (data.destinationRectangle == nullptr)
    {
        p_destRect = NULL;
    }
    else
    {
        Pair<int, int> adjustedOrigin(data.destinationRectangle->x, data.destinationRectangle->y);
        _cameras.adjustPosition(adjustedOrigin);

        Rectangle adjustedRectangle(adjustedOrigin.first, adjustedOrigin.second, data.destinationRectangle->width, data.destinationRectangle->height);

        destRect = adjustedRectangle.toSDLRect();
        p_destRect = &destRect;
    }

    SDL_Point center;
    SDL_Point *p_center;
    if (data.center == nullptr)
    {
        p_center = NULL;
    }
    else
    {
        center = data.center->toSDLPoint();
        p_center = &center;
    }

    SDL_RenderCopyEx(_renderer.getSDLRendererObject(), getTexture(filename).getSDLTextureObject(), p_srcRect, p_destRect, data.angle, p_center, static_cast<SDL_RendererFlip>(data.flip));
}

void Graphics::drawTexture(string filename)
{
    TextureDrawData newDrawData;
    drawTexture(filename, newDrawData);
}

void Graphics::setWindowDimensions(int width, int height)
{
    _window.setDimensions(width, height);
}

void Graphics::setWindowDimensions(const Pair<int, int>& dimensions)
{
    _window.setDimensions(dimensions);
}

Pair<int, int> Graphics::getWindowDimensions() const
{
    return _window.getDimensions();
}

void Graphics::setWindowFullscreen(bool isFullscreen)
{
    _window.setFullscreen(isFullscreen);
}

void Graphics::setWindowBordered(bool isBordered)
{
    _window.setBordered(isBordered);
}

void Graphics::setWindowResizable(bool isResizable)
{
    _window.setResizable(isResizable);
}

void Graphics::setRenderDimensions(int width, int height)
{
    _renderer.setLogicalDimensions(width, height);
}

void Graphics::setRenderDimensions(Pair<int, int>& dimensions)
{
    _renderer.setLogicalDimensions(dimensions);
}

void Graphics::setRenderScalingFactor(float scalingX, float scalingY)
{
    _renderer.setScalingFactor(scalingX, scalingY);
}

void Graphics::setRenderScalingFactor(const Pair<float, float>& scalingFactors)
{
    _renderer.setScalingFactor(scalingFactors);
}

void Graphics::setRenderViewport(const Rectangle& viewport)
{
    _renderer.setViewport(viewport);
}

void Graphics::setRenderVSync(const bool useVSync)
{
    _renderer.setVSync(useVSync);
}

void Graphics::drawText(string text, TextDrawData& data, int x, int y)
{
    
}

void Graphics::drawText(string text, TextDrawData& data, Pair<int, int> position)
{

}

int Graphics::addCamera(Camera *camera)
{
    return _cameras.addCamera(camera);
}

void Graphics::setCamera(int cameraID)
{
    _cameras.setCamera(cameraID);
}

void Graphics::setCameraX(double x)
{
    _cameras.setCameraPosition(x, _cameras.getPosition().second);
}

void Graphics::setCameraY(double y)
{
    _cameras.setCameraPosition(_cameras.getPosition().first, y);
}

void Graphics::setCameraPosition(double x, double y)
{
    _cameras.setCameraPosition(x, y);
}

void Graphics::setCameraPosition(const Pair<double, double>& position)
{
    _cameras.setCameraPosition(position);
}

const Pair<double, double>& Graphics::getCameraPosition()
{
    return _cameras.getPosition();
}

void Graphics::updateCamera()
{
    _cameras.update();
}

void Graphics::fill(const Colour &colour)
{
    _renderer.setDrawColour(colour);
    SDL_RenderClear(_renderer.getSDLRendererObject());
}

void Graphics::present()
{
    SDL_RenderPresent(_renderer.getSDLRendererObject());
}

const Window& Graphics::getWindow() const
{
    return _window;
}

const Renderer& Graphics::getRenderer() const
{
    return _renderer;
}

