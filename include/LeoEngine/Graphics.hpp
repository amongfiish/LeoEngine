#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <string>
#include "LeoEngine/Window.hpp"
#include "LeoEngine/Renderer.hpp"
#include "LeoEngine/Texture.hpp"
#include "LeoEngine/TextureDrawData.hpp"
#include "LeoEngine/TextDrawData.hpp"
#include "LeoEngine/Loader.hpp"
#include "LeoEngine/FontManager.hpp"
#include "LeoEngine/CameraManager.hpp"
#include "LeoEngine/Line.hpp"

namespace LeoEngine
{

    class RenderTarget;

    class Graphics
    {
    public:
        Graphics();
        ~Graphics();

        // primitive drawing functions
        void drawPoint(const Colour &colour, const int x, const int y);
        void drawPoint(const Colour &colour, const Pair<int, int> &point);

        void drawLine(const Colour &colour, const int x0, const int y0, const int x1, const int y1);
        void drawLine(const Colour &colour, const Pair<int, int> &start, const Pair<int, int> &end);
        void drawLine(const Colour &colour, const Line &line);

        void drawRectangle(const Colour &colour, bool fill, const int x, const int y, const int width, const int height);
        void drawRectangle(const Colour &colour, bool fill, const Pair<int, int> &origin, const Pair<int, int> &opposite);
        void drawRectangle(const Colour &colour, bool fill, const Rectangle &rectangle);

        // texture functions
        Texture &getTexture(std::string filename);

        void drawTexture(std::string filename, const TextureDrawData &data);
        void drawTexture(std::string filename);
        void drawTexture(Texture *texture, const TextureDrawData &data);
        void drawTexture(Texture *texture);

        void drawTextureCameraless(Texture *texture, const TextureDrawData &data);
        void drawTextureCameraless(Texture *texture);

        void copyRenderTarget(RenderTarget &renderTarget, double opacity);

        // window functions
        void setWindowDimensions(int width, int height);
        void setWindowDimensions(const Pair<int, int> &dimensions);

        Pair<int, int> getWindowDimensions() const;

        void setWindowFullscreen(bool isFullscreen);
        void setWindowBordered(bool isBordered);
        void setWindowResizable(bool isResizable);

        void setWindowTitle(std::string title);

        // renderer functions
        void setRenderDimensions(int width, int height);
        void setRenderDimensions(Pair<int, int> &dimensions);

        void setRenderScalingFactor(float scalingX, float scalingY);
        void setRenderScalingFactor(const Pair<float, float> &scalingFactors);

        void setRenderViewport(const Rectangle &viewport);

        void setRenderVSync(bool useVSync);

        void setRenderTarget(RenderTarget *renderTarget);

        // font functions
        Texture *renderText(std::string text, TextDrawData& data);

        // camera functions
        bool cameraExists();

        int addCamera(Camera *camera);
        void setCamera(int cameraID);

        void setCameraX(double x);
        void setCameraY(double y);
        void setCameraPosition(double x, double y);
        void setCameraPosition(const Pair<double, double> &position);
        const Pair<double, double> &getCameraPosition();

        void updateCamera();

        // additional stuff
        void fill(const Colour &colour);
        void present();

        // not sure about this
        const Window &getWindow() const;
        const Renderer &getRenderer() const;

    private:
        Window _window;
        Renderer _renderer;

        Loader<Texture> _textureLoader;
        FontManager _fontManager;

        CameraManager _cameras;
    };

}

#endif

