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

bool ResourceManager::hasShaderProgram(const char * pathToVerticesShader, const char * pathToFragmentShader, bool isPath)
{
    std::string paths = std::string(pathToVerticesShader) + std::string(pathToFragmentShader);
    std::hash<std::string> hash;
    size_t key = hash(paths);

    if (m_shaderPrograms.find(key) == m_shaderPrograms.end())
    {
        return false;
    }
    return true;
}

bool ResourceManager::createShaderProgram(const char * pathToVerticesShader, const char * pathToFragmentShader, bool isPath)
{
    std::string paths = std::string(pathToVerticesShader) + std::string(pathToFragmentShader);
    std::hash<std::string> hash;
    size_t key = hash(paths);

    ShaderProgram * program = new ShaderProgram();

    std::map<ShaderType, const char *> pathes = {
        {ShaderType::VertexShader, pathToVerticesShader},
        {ShaderType::FragmentShader, pathToFragmentShader}
    };

    Shader * shader = nullptr;

    for (auto & i : pathes)
    {
        if (!hasShader(i.second, isPath))
        {
            if (createShader(i.second, i.first, isPath))
            {
                shader = getShader(i.second, isPath);
                program->attach(i.first, shader);
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }

    if (!program->link())
    {
        std::cout << "Failed shaders linkage!" << std::endl;
        return false;
    }

    m_shaderPrograms[key] = program;
    return true;
}

ShaderProgram *ResourceManager::getShaderProgram(const char * pathToVerticesShader, const char * pathToFragmentShader, bool isPath)
{
    std::string paths = std::string(pathToVerticesShader) + std::string(pathToFragmentShader);
    std::hash<std::string> hash;
    size_t key = hash(paths);
    if (m_shaderPrograms.find(key) == m_shaderPrograms.end())
    {
        if (!createShaderProgram(pathToVerticesShader, pathToFragmentShader))
        {
            return nullptr;
        }
    }

    return m_shaderPrograms[key];
}

bool ResourceManager::hasShader(const char * path, bool isPath)
{
    std::string key = std::string(path);
    if (m_shaders.find(key) == m_shaders.end())
    {
        return false;
    }
    return true;
}

bool ResourceManager::createShader(const char * path, const ShaderType & type, bool isPath)
{
    std::string key = std::string(path);

    std::ifstream file;

    file.open(path);

    if (!file.good())
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

Shader * ResourceManager::getShader(const char * path, bool isPath)
{
    std::string key = std::string(path);
    if (m_shaders.find(key) == m_shaders.end())
    {
        return nullptr;
    }

    return m_shaders[key];
}

}
