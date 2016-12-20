#pragma once

#include "vec4.hpp"

namespace glRender
{

class Camera;
class Scene;

class Render
{
    Render();
public:
    static Render * instance();
    const char * contextInformation();
    void draw(Scene * scene);
    void setViewportSize(const int & w, const int & h);
    void setBackgroundColor(const Vec4 & background);
private:
    Vec4 m_background = {0.5f, 0.5f, 0.5f, 1.0f};

};

}
