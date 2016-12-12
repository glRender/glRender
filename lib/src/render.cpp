#include "render.hpp"
#include "scene.hpp"
#include "opengl.h"

using namespace glRender;

Render::Render()
{
}

void Render::draw(Scene *scene)
{
    glClearColor ( 0.5, 0.5, 0.5, 1.0 );
    glEnable     ( GL_DEPTH_TEST );
    glEnable     ( GL_BLEND);
    glDepthFunc  ( GL_LEQUAL );
    glBlendFunc  ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClear      ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    scene->draw();
}

void Render::setViewPortSize(int w, int h)
{
    glViewport ( 0, 0, (GLsizei)w, (GLsizei)h );
}

bool Render::glLoad()
{
    return gladLoadGL();
}
