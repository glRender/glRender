#pragma once

#include "glRender.h"

namespace glRender {

class AABBNodeVisualizator : public NodeMixedWith<IUpdateable, IDrawable>
{
public:
        AABBNodeVisualizator(AABB * aabb);
        void update() override;
        void draw(CameraPtr camera) override;
private:
        AABB * m_aabb = nullptr;
        Model * m_corner = nullptr;
};

}
