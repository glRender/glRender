#include "resourceManager.hpp"

namespace glRender {

glRender::Texture *glRender::ResourceManager::getTexture(const char * path)
{
    std::string key = std::string(path);
    if (m_textures.find(key) == m_textures.end())
    {
        m_textures[key] = new Texture(path);
    }

    return m_textures[key];
}

ShaderProgram *ResourceManager::getShaderProgram(const char * pathToVerticesShader, const char * pathToFragmentShader)
{
    std::string key = std::string(pathToVerticesShader) + std::string(pathToFragmentShader);
    if (m_shaderPrograms.find(key) == m_shaderPrograms.end())
    {
        m_shaderPrograms[key] = new ShaderProgram(pathToVerticesShader, pathToFragmentShader);
    }

    return m_shaderPrograms[key];
}

bool ResourceManager::hasShader(const char * path)
{
    std::string key = std::string(path);
    if (m_shaders.find(key) == m_shaders.end())
    {
        return false;
    }
    return true;
}

bool ResourceManager::initShader(const char * path, const GLenum & type)
{
    std::string key = std::string(path);
    Shader * shader = new Shader(type);

    bool isCompiled = false;
    bool isLoadedFromFile = false;

    isLoadedFromFile = shader->loadFromFile(path);
    if (isLoadedFromFile)
    {
        isCompiled = shader->compile();
    }

    if (!isLoadedFromFile)
    {
        std::cout << "Can't shader from file!" << std::endl;
        return false;
    }

    if (!isCompiled)
    {
        std::cout << "Can't compile shader!" << std::endl;
        return false;
    }

    m_shaders[key] = shader;
    return true;
}

Shader *ResourceManager::getShader(const char * path)
{
    std::string key = std::string(path);
    if (m_shaders.find(key) == m_shaders.end())
    {
        return nullptr;
    }

    return m_shaders[key];
}

}
