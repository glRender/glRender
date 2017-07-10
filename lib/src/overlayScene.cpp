#include "overlayScene.hpp"

#include "opengl.h"

using namespace glRender;

OverlayScene::OverlayScene()
{
    eventManager().setHandler(Scene::Event::PrevDraw, []() {
        glDisable    (GL_DEPTH_TEST);
    });
}

OverlayScene::~OverlayScene()
{

}
