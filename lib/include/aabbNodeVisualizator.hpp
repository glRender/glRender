#pragma once

#include "visitor.hpp"
#include "aabb.hpp"
#include "vec3.hpp"
#include "node.hpp"
#include "model.hpp"
#include "camera.hpp"

namespace glRender {

class AABBNodeVisualizator/* : public IDrawable*/
{
public:
        AABBNodeVisualizator(AABB * aabb);
        void update() /*override*/;
        void draw(CameraPtr camera) /*override*/;
private:
        AABB * m_aabb = nullptr;
        Model * m_corner = nullptr;
};

}
