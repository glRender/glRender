#include "underOverlayScene.hpp"

#include "opengl.h"

using namespace glRender;

UnderOverlayScene::UnderOverlayScene()
{
    eventManager().setHandler(Scene::Event::PrevDraw, []() {
        glDepthRange(0.1, 1.0);
    });
}

UnderOverlayScene::~UnderOverlayScene()
{

}
