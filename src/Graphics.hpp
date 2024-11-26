#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <string>
#include "Window.hpp"
#include "Renderer.hpp"
#include "Texture.hpp"
#include "TextureDrawData.hpp"
#include "Font.hpp"
#include "TextDrawData.hpp"
#include "Loader.hpp"
#include "CameraManager.hpp"
using namespace std;

class Graphics
{
public:
    Graphics();
    ~Graphics();

    // primitive drawing functions
    void drawPoint(const Colour& colour, const int x, const int y);
    void drawPoint(const Colour& colour, const Pair<int, int>& point);
    
    void drawLine(const Colour& colour, const int x0, const int y0, const int x1, const int y1);
    void drawLine(const Colour& colour, const Pair<int, int>& start, const Pair<int, int>& end);

    void drawRectangle(const Colour& colour, bool fill, const int x, const int y, const int width, const int height);
    void drawRectangle(const Colour& colour, bool fill, const Pair<int, int>& origin, const Pair<int, int>& opposite);
    void drawRectangle(const Colour& colour, bool fill, const Rectangle& rectangle);

    // texture functions
    Texture& getTexture(string filename);

    void drawTexture(string filename, const TextureDrawData& data);
    void drawTexture(string filename);

    // window functions
    void setWindowDimensions(int width, int height);
    void setWindowDimensions(const Pair<int, int>& dimensions);

    Pair<int, int> getWindowDimensions() const;

    void setWindowFullscreen(bool isFullscreen);
    void setWindowBordered(bool isBordered);
    void setWindowResizable(bool isResizable);

    // renderer functions
    void setRenderDimensions(int width, int height);
    void setRenderDimensions(Pair<int, int>& dimensions);

    void setRenderScalingFactor(float scalingX, float scalingY);
    void setRenderScalingFactor(const Pair<float, float>& scalingFactors);

    void setRenderViewport(const Rectangle& viewport);

    void setRenderVSync(bool useVSync);

    // font functions
    void drawText(string text, TextDrawData& data, int x, int y);
    void drawText(string text, TextDrawData& data, Pair<int, int> position);

    // camera functions
    int addCamera(Camera *camera);
    void setCamera(int cameraID);

    void setCameraX(double x);
    void setCameraY(double y);
    void setCameraPosition(double x, double y);
    void setCameraPosition(const Pair<double, double>& position);
    const Pair<double, double>& getCameraPosition();

    void updateCamera();

    // additional stuff
    void fill(const Colour& colour);
    void present();

    // not sure about this
    const Window& getWindow() const;
    const Renderer& getRenderer() const;

private:
    Window _window;
    Renderer _renderer;

    Loader<Texture> _textureLoader;
    Loader<Font> _fontLoader;

    CameraManager _cameras;
};

#endif

