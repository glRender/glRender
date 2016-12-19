#include "render.hpp"
#include "scene.hpp"
#include "opengl.h"

using namespace glRender;

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

const char * getGLString(uint key)
{
    return reinterpret_cast<const char*>(glGetString(key));
}

const char * Render::contextInformation()
{
    std::string contextInformation;
    contextInformation += std::string("Vendor:   ") + getGLString(GL_VENDOR) + '\n';
    contextInformation += std::string("Renderer: ") + getGLString(GL_RENDERER) + '\n';
    contextInformation += std::string("Version:  ") + getGLString(GL_VERSION) + '\n';
    contextInformation += std::string("GLSL:     ") + getGLString(GL_SHADING_LANGUAGE_VERSION);
    return contextInformation.c_str();
}
