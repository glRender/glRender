#pragma once

namespace glRender
{

class Camera;
class Scene;

class Render
{
public:
    Render();

    void draw(Scene * scene);
    void setViewPortSize(int w, int h);

    static bool glLoad();
};

}
