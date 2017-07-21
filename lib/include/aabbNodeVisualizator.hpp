#pragma once

#include "base.h"

#include "nodeMixer.hpp"

namespace glRender {

class AABB;
class Camera;
class Model;

class AABBNodeVisualizator : public NodeMixedWith<IUpdateable, IDrawable>
{
public:
        AABBNodeVisualizator(AABB * aabb);
        void update() override;
        void draw(Camera * camera) override;
private:
        AABB * m_aabb = nullptr;
        Model * m_corner = nullptr;
};

}
