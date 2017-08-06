#pragma once

#include "vec4.hpp"
#include "orderedScenes.hpp"
#include "nodeMixer.hpp"

namespace glRender
{

class Camera;
class Scene;

class Render
{
    Render();
public:
    Render(const Render&) = delete;
    Render & operator=(const Render&) = delete;

    static Render * instance();
    const char * contextInformation() const;
    const char * versionInformation();

    void drawFrame();
    void update();
    void processKeyboardsKeys(IKeyPressable::KeyboardKey key);

    void setViewportSize(uint width, uint heigth);
    void setBackgroundColor(const Vec4 & background);
    OrderedScenes & scenes();

private:
    Vec4 m_background = {0.5f, 0.5f, 0.5f, 1.0f};
    OrderedScenes m_scenes;

};

}
