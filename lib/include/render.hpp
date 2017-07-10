#pragma once

#include "vec4.hpp"

#include "orderedScenes.hpp"

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
    const char * contextInformation();
    void drawFrame();
    void update();
    void setViewportSize(const uint32_t & w, const uint32_t & h);
    void setBackgroundColor(const Vec4 & background);
    OrderedScenes & scenes();

private:
    Vec4 m_background = {0.5f, 0.5f, 0.5f, 1.0f};
    OrderedScenes m_scenes;

};

}
