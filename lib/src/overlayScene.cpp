#include "overlayScene.hpp"

#include "opengl.h"

using namespace glRender;

OverlayScene::OverlayScene()
{
    eventManager().setHandler(Scene::Event::PrevDraw, []() {
        glDepthRange(0.0, 0.1);
    });
}

OverlayScene::~OverlayScene()
{

}
