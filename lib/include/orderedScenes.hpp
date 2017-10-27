#pragma once

#include "base.h"

namespace glRender
{

class Scene;

class OrderedScenes
{
public:
    void add(Scene * scene);
    void add(Scene * scene, float zIndex);

    void remove(Scene * scene);
    float zIndex(Scene * scene) const;
    void editZIndex(Scene * scene, float zIndex);
    std::list<Scene *> scenes() const;
private:
    void insert(std::list<Scene *>::iterator it, Scene * scene);

private:
    std::list<Scene *> m_orderedScenes;
    float maxZIndex = 0;
};

}

