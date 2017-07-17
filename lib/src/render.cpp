#include "render.hpp"
#include "scene.hpp"
#include "opengl.h"

using namespace glRender;

void APIENTRY glDebugOutput(uint32_t source,
                            uint32_t type,
                            uint32_t id,
                            uint32_t severity,
                            int length,
                            const char * message,
                            const void * userParam)
{
    // ignore non-significant error/warning codes
    if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

    std::cout << "---------------" << std::endl;
    std::cout << "Debug message (" << id << "): " <<  message << std::endl;

    switch (source)
    {
        case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
        case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
    } std::cout << std::endl;

    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
        case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
        case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
    } std::cout << std::endl;

    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
        case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
        case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
    } std::cout << std::endl;
    std::cout << std::endl;
}

Render::Render()
{

}

void Render::drawFrame()
{
    glClearColor ( m_background.x, m_background.y, m_background.z, m_background.w );
    glEnable     ( GL_DEPTH_TEST );
    glEnable     ( GL_BLEND);
    glDepthFunc  ( GL_LEQUAL );
    glBlendFunc  ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClear      ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    for (auto i : m_scenes.scenes())
    {
        i->drawFrame();
    }

}

void Render::update()
{
    for (auto i : m_scenes.scenes())
    {
        i->update();
    }
}

void Render::processKeyboardsKeys(IKeyPressable::KeyboardKey key)
{
    for (auto i : m_scenes.scenes())
    {
        i->processKeyboardsKeys(key);
    }
}

void Render::setViewportSize(uint width, uint height)
{
    glViewport(0, 0, width, height);
}

void Render::setBackgroundColor(const Vec4 &background)
{
    m_background = background;
}

OrderedScenes & Render::scenes()
{
    return m_scenes;
}

Render * Render::instance()
{
    static Render * instance = nullptr;

    if (instance == nullptr)
    {
        if (gladLoadGL())
        {
            if (GL_CONTEXT_FLAG_DEBUG_BIT)
            {
//                glEnable(GL_DEBUG_OUTPUT);
//                glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
//                glDebugMessageCallback(glDebugOutput, nullptr);
//                glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
            }

            instance = new Render();
        }
    }

    return instance;
}

const char * getGLString(uint32_t key)
{
    return reinterpret_cast<const char*>(glGetString(key));
}

const char * Render::contextInformation()
{
    int maxTextureUnits = 0;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureUnits);

    int maxTextureSize = 0;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize);

    int maxElementsVertices = 0;
    glGetIntegerv(GL_MAX_ELEMENTS_VERTICES, &maxElementsVertices);

    int maxElementsIndices = 0;
    glGetIntegerv(GL_MAX_ELEMENTS_INDICES, &maxElementsIndices);

    int maxPointSize = 0;
    glGetIntegerv(GL_POINT_SIZE_MAX, &maxPointSize);

    int minPointSize = 0;
    glGetIntegerv(GL_POINT_SIZE_MIN, &minPointSize);

    int maxDrawBuffers = 0;
    glGetIntegerv(GL_MAX_DRAW_BUFFERS, &maxDrawBuffers);

    int maxVertexAttribs = 0;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertexAttribs);

    int maxVertexUniformsComponents = 0;
    glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &maxVertexUniformsComponents);

    int maxFragmentUniformsComponents = 0;
    glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS, &maxFragmentUniformsComponents);

    int maxGeometryUniformsComponents = 0;
    glGetIntegerv(GL_MAX_GEOMETRY_UNIFORM_COMPONENTS, &maxGeometryUniformsComponents);

    int maxRenderBufferSize = 0;
    glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &maxRenderBufferSize);

    int maxFramebufferWidth = 0;
    glGetIntegerv(GL_MAX_FRAMEBUFFER_WIDTH, &maxFramebufferWidth);

    int maxFramebufferHeight = 0;
    glGetIntegerv(GL_MAX_FRAMEBUFFER_HEIGHT, &maxFramebufferHeight);

    std::string contextInformation;
    contextInformation += std::string("Vendor                           : ") + getGLString(GL_VENDOR) + '\n';
    contextInformation += std::string("GPU                              : ") + getGLString(GL_RENDERER) + '\n';
    contextInformation += std::string("OpenGL version                   : ") + getGLString(GL_VERSION) + '\n';
    contextInformation += std::string("GLSL version                     : ") + getGLString(GL_SHADING_LANGUAGE_VERSION) + '\n';
    contextInformation += std::string("Max texture units number         : ") + patch::to_string(maxTextureUnits) + '\n';
    contextInformation += std::string("Max texture size                 : ") + patch::to_string(maxTextureSize) + '\n';
    contextInformation += std::string("Max elements vertices            : ") + patch::to_string(maxElementsVertices) + '\n';
    contextInformation += std::string("Max elements indices             : ") + patch::to_string(maxElementsIndices) + '\n';
    contextInformation += std::string("Max point size                   : ") + patch::to_string(maxPointSize) + '\n';
    contextInformation += std::string("Min point size                   : ") + patch::to_string(minPointSize) + '\n';
    contextInformation += std::string("Max vertex attribs               : ") + patch::to_string(maxVertexAttribs) + '\n';
    contextInformation += std::string("Max vertex uniforms components   : ") + patch::to_string(maxVertexUniformsComponents) + '\n';
    contextInformation += std::string("Max fragment uniforms components : ") + patch::to_string(maxFragmentUniformsComponents) + '\n';
    contextInformation += std::string("Max geometry uniforms components : ") + patch::to_string(maxGeometryUniformsComponents) + '\n';
    contextInformation += std::string("Max framebuffer width            : ") + patch::to_string(maxFramebufferWidth) + '\n';
    contextInformation += std::string("Max framebuffer height           : ") + patch::to_string(maxFramebufferHeight) + '\n';

    return contextInformation.c_str();
}
