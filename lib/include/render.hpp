#pragma once

namespace glRender
{

class Camera;
class Scene;

class Render
{
public:
    static bool glLoad();
    static const char * contextInformation();
    static void draw(Scene * scene);
    static void setViewPortSize(int w, int h);
};

}
