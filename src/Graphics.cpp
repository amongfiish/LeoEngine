#if defined(__linux__) || defined(__APPLE__)
    #include <SDL3/SDL.h>
    #include <SDL3_image/SDL_image.h>
    #include <SDL3_ttf/SDL_ttf.h>
#elif defined(_WIN32)
    #include <SDL.h>
    #include <SDL_image.h>
    #include <SDL_ttf.h>
#endif

#include <stdexcept>
#include <iostream>

#include "LeoEngine/Graphics.hpp"
#include "LeoEngine/Pair.hpp"
#include "LeoEngine/RenderTarget.hpp"
#include "LeoEngine/Collision.hpp"

namespace LeoEngine
{

    Graphics::Graphics()
            : _window(),
            _renderer(_window.getSDLWindowObject()),
            _textureLoader("textures")
    {
        if (!SDL_InitSubSystem(SDL_INIT_VIDEO))
        {
            throw std::runtime_error("Couldn't initialize SDL video subsystem.");
        }

        if (!TTF_Init())
        {
            throw std::runtime_error("Couldn't initialize SDL TTF.");
        }
    }

    Graphics::~Graphics()
    {
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
        TTF_Quit();
    }

    void Graphics::postInitialization()
    {
        _window.postInitialization();
    }

    void Graphics::drawPoint(const Colour& colour, const int x, const int y)
    {
        Pair<int, int> adjustedPoint(x, y);
        _cameras.adjustPosition(adjustedPoint);
        
        _renderer.setDrawColour(colour);
        SDL_RenderPoint(_renderer.getSDLRendererObject(), adjustedPoint.first, adjustedPoint.second);
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
        SDL_RenderLine(_renderer.getSDLRendererObject(), adjustedStart.first, adjustedStart.second, adjustedEnd.first, adjustedEnd.second);
    }

    void Graphics::drawLine(const Colour& colour, const Pair<int, int>& start, const Pair<int, int>& end)
    {
        drawLine(colour, start.first, start.second, end.first, end.second);
    }

    void Graphics::drawLine(const Colour &colour, const Line &line)
    {
        drawLine(colour, line.start, line.end);
    }

    void Graphics::drawRectangle(const Colour& colour, bool fill, const int x, const int y, const int width, const int height)
    {
        Pair<int, int> adjustedOrigin(x, y);
        _cameras.adjustPosition(adjustedOrigin);
        SDL_FRect newFRect = { static_cast<float>(adjustedOrigin.first), static_cast<float>(adjustedOrigin.second), static_cast<float>(width), static_cast<float>(height) };

        _renderer.setDrawColour(colour);
        if (fill)
        {
            SDL_RenderFillRect(_renderer.getSDLRendererObject(), &newFRect);
        }
        else
        {
            SDL_RenderRect(_renderer.getSDLRendererObject(), &newFRect);
        }
    }

    void Graphics::drawRectangle(const Colour& colour, bool fill, const Pair<int, int>& origin, const Pair<int, int>& opposite)
    {
        drawRectangle(colour, fill, origin.first, origin.second, opposite.first, opposite.second);
    }

    void Graphics::drawRectangle(const Colour& colour, bool fill, const Rectangle<int>& rectangle)
    {
        drawRectangle(colour, fill, rectangle.x, rectangle.y, rectangle.width, rectangle.height);
    }

    void Graphics::drawRectangleCameraless(const Colour &colour, bool fill, const int x, const int y, const int width, const int height)
    {
        SDL_FRect newFRect = { static_cast<float>(x), static_cast<float>(y), static_cast<float>(width), static_cast<float>(height) };
        
        _renderer.setDrawColour(colour);
        if (fill)
        {
            SDL_RenderFillRect(_renderer.getSDLRendererObject(), &newFRect);
        }
        else
        {
            SDL_RenderRect(_renderer.getSDLRendererObject(), &newFRect);
        }
    }

    void Graphics::drawRectangleCameraless(const Colour &colour, bool fill, const Pair<int, int> &origin, const Pair<int, int> &opposite)
    {
        drawRectangleCameraless(colour, fill, origin.first, origin.second, opposite.first, opposite.second);
    }

    void Graphics::drawRectangleCameraless(const Colour &colour, bool fill, const Rectangle<int> &rectangle)
    {
        drawRectangleCameraless(colour, fill, rectangle.x, rectangle.y, rectangle.width, rectangle.height);
    }

    Texture& Graphics::getTexture(std::string filename)
    {
        return _textureLoader.get(filename);
    }

    void Graphics::drawTexture(std::string filename, const TextureDrawData& data)
    {
        drawTexture(getTexture(filename), data);
    }

    void Graphics::drawTexture(std::string filename)
    {
        TextureDrawData newDrawData;
        drawTexture(filename, newDrawData);
    }

    void Graphics::drawTexture(Texture& texture, const TextureDrawData& data)
    {
        SDL_FRect srcFRect;
        SDL_FRect *p_srcFRect;
        if (data.sourceRectangle == nullptr)
        {
            p_srcFRect = NULL;
        }
        else
        {
            srcFRect.x = data.sourceRectangle->x;
            srcFRect.y = data.sourceRectangle->y;
            srcFRect.w = data.sourceRectangle->width;
            srcFRect.h = data.sourceRectangle->height;
            p_srcFRect = &srcFRect;
        }

        SDL_FRect destFRect;
        SDL_FRect *p_destFRect;
        if (data.destinationRectangle == nullptr)
        {
            p_destFRect = NULL;
        }
        else
        {
            Pair<int, int> adjustedOrigin(data.destinationRectangle->x, data.destinationRectangle->y);
            _cameras.adjustPosition(adjustedOrigin);

            Rectangle<int> adjustedRectangle(adjustedOrigin.first, adjustedOrigin.second, data.destinationRectangle->width, data.destinationRectangle->height);

            destFRect.x = adjustedRectangle.x;
            destFRect.y = adjustedRectangle.y;
            destFRect.w = adjustedRectangle.width;
            destFRect.h = adjustedRectangle.height;
            p_destFRect = &destFRect;
        }

        SDL_FPoint center;
        SDL_FPoint *p_center;
        if (data.center == nullptr)
        {
            p_center = NULL;
        }
        else
        {
            center.x = data.center->first;
            center.y = data.center->second;
            p_center = &center;
        }

        SDL_RenderTextureRotated(_renderer.getSDLRendererObject(), texture.getSDLTextureObject(), p_srcFRect, p_destFRect, data.angle, p_center, static_cast<SDL_FlipMode>(data.flip));
    }

    void Graphics::drawTexture(Texture& texture)
    {
        TextureDrawData newDrawData;
        drawTexture(texture, newDrawData);
    }

    void Graphics::drawTextureCameraless(std::string filename, const TextureDrawData &data)
    {
        drawTextureCameraless(getTexture(filename), data);
    }

    void Graphics::drawTextureCameraless(std::string filename)
    {
        drawTextureCameraless(getTexture(filename));
    }

    void Graphics::drawTextureCameraless(Texture& texture, const TextureDrawData &data)
    {
        const Pair<double, double> cameraPosition = _cameras.getPosition();
        _cameras.setCameraPosition(0, 0);

        drawTexture(texture, data);

        _cameras.setCameraPosition(cameraPosition);
    }

    void Graphics::drawTextureCameraless(Texture& texture)
    {
        TextureDrawData newDrawData;
        drawTextureCameraless(texture, newDrawData);
    }

    void Graphics::copyRenderTarget(RenderTarget &renderTarget, double opacity)
    {
        if (renderTarget.getSDLTextureObject() == nullptr)
        {
            std::string errorMessage = "Attempted to copy render target that wasn't properly initialized.";
            Services::get().getLogger()->error("Graphics", errorMessage);
            Services::get().getLogger()->flush();
            throw std::runtime_error(errorMessage);
        }

        SDL_SetTextureAlphaMod(renderTarget.getSDLTextureObject(), static_cast<int>(255 * opacity));
        SDL_RenderTexture(_renderer.getSDLRendererObject(), renderTarget.getSDLTextureObject(), NULL, NULL);
        SDL_SetTextureAlphaMod(renderTarget.getSDLTextureObject(), 255);
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

    void Graphics::setWindowGrabCursor(bool grabCursor)
    {
        _window.setGrabCursor(grabCursor);
    }

    void Graphics::setWindowTitle(std::string title)
    {
        _window.setTitle(title);
    }

    void Graphics::setRenderDimensions(int width, int height)
    {
        _renderer.setLogicalDimensions(width, height);
    }

    void Graphics::setRenderDimensions(Pair<int, int>& dimensions)
    {
        _renderer.setLogicalDimensions(dimensions);
    }

    Pair<int, int> Graphics::getRenderDimensions() const
    {
        return _renderer.getLogicalDimensions();
    }

    void Graphics::setRenderScalingFactor(float scalingX, float scalingY)
    {
        _renderer.setScalingFactor(scalingX, scalingY);
    }

    void Graphics::setRenderScalingFactor(const Pair<float, float>& scalingFactors)
    {
        _renderer.setScalingFactor(scalingFactors);
    }

    void Graphics::setRenderViewport(const Rectangle<int>& viewport)
    {
        _renderer.setViewport(viewport);
    }

    void Graphics::setRenderVSync(const bool useVSync)
    {
        _renderer.setVSync(useVSync);
    }

    void Graphics::setRenderTarget(RenderTarget *renderTarget)
    {
        SDL_Texture *target = nullptr;

        if (renderTarget != nullptr)
        {
            target = renderTarget->getSDLTextureObject();
        }

        SDL_SetRenderTarget(_renderer.getSDLRendererObject(), target);
    }

    std::shared_ptr<Texture> Graphics::renderText(std::string text, TextDrawData& data)
    {
        TTF_Font *font = _fontManager.getFont(data.fontFilename, data.pointSize);
        SDL_Surface *renderedText = TTF_RenderText_Solid(font, text.c_str(), text.size(), data.colour.toSDLColor());
        if (renderedText == nullptr)
        {
            std::string errorMessage = std::string("Failed to render text. SDL error text: '") + SDL_GetError() + "'.";
            Services::get().getLogger()->error("Graphics", errorMessage);
            Services::get().getLogger()->flush();
            throw std::runtime_error(errorMessage);
        }

        std::shared_ptr<Texture> newTexture = std::make_shared<Texture>(renderedText);
        SDL_DestroySurface(renderedText);

        return newTexture;
    }

    bool Graphics::cameraExists()
    {
        return _cameras.currentCameraExists();
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

    const Pair<double, double>& Graphics::getCameraPosition() const
    {
        return _cameras.getPosition();
    }

    Rectangle<int> Graphics::getVisibleRegionRectangle() const
    {
        const Pair<double, double>& cameraPosition = getCameraPosition();
        Pair<int, int> cameraPositionAsIntegers(cameraPosition.first, cameraPosition.second);
        Rectangle<int> visibleRegion(cameraPositionAsIntegers, getRenderDimensions());

        return visibleRegion;
    }

    void Graphics::updateCamera()
    {
        _cameras.update();
    }

    bool Graphics::checkPointVisibility(const Pair<int, int>& point) const
    {
        return checkForOverlap(point, getVisibleRegionRectangle());
    }

    bool Graphics::checkRectangleVisibility(const Rectangle<int>& rectangle) const
    {
        return checkForOverlap(rectangle, getVisibleRegionRectangle());
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

}
