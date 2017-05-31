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

bool ResourceManager::createShader(const char * path, const ShaderType & type)
{
    std::string key = std::string(path);

    std::ifstream file;

    file.open(path);

    if (!file.good() )
    {
        std::cout << "Failed to open file: " << path << std::endl;
        return false;
    }

    std::stringstream stream;
    stream << file.rdbuf();
    file.close();

    std::string text = stream.str();

    Shader * shader = new Shader(text.c_str(), type);
    if (!shader->compile())
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
