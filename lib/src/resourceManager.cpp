#include "resourceManager.hpp"

namespace glRender {

//glRender::Texture *glRender::ResourceManager::getTexture(const char * path)
//{
//    std::string key = std::string(path);
//    if (m_textures.find(key) == m_textures.end())
//    {
//        m_textures[key] = new Texture(path);
//    }

//    return m_textures[key];
//}

//bool ResourceManager::hasShaderProgram(const char * pathToVerticesShader, const char * pathToFragmentShader, bool isPath)
//{
//    std::string paths = std::string(pathToVerticesShader) + std::string(pathToFragmentShader);
//    std::hash<std::string> hash;
//    size_t key = hash(paths);

//    if (m_shaderPrograms.find(key) == m_shaderPrograms.end())
//    {
//        return false;
//    }
//    return true;
//}

//bool ResourceManager::createShaderProgram(const char * pathToVerticesShader, const char * pathToFragmentShader, bool isPath)
//{
//    std::string paths = std::string(pathToVerticesShader) + std::string(pathToFragmentShader);
//    std::hash<std::string> hash;
//    size_t key = hash(paths);

//    ShaderProgram * program = new ShaderProgram();

//    std::map<ShaderType, const char *> pathes = {
//        {ShaderType::VertexShader, pathToVerticesShader},
//        {ShaderType::FragmentShader, pathToFragmentShader}
//    };


//    for (auto & i : pathes)
//    {
//        if (!hasShader(i.second, isPath))
//        {
//            if (createShader(i.second, i.first, isPath))
//            {
//                std::shared_ptr<Shader> shader = getShader(i.second, isPath);
//                program->attach(i.first, shader);
//            }
//            else
//            {
//                return false;
//            }
//        }
//        else
//        {
//            return false;
//        }
//    }

//    if (!program->link())
//    {
//        std::cout << "Failed shaders linkage!" << std::endl;
//        return false;
//    }

//    m_shaderPrograms[key] = program;
//    return true;
//}

//ShaderProgram *ResourceManager::getShaderProgram(const char * pathToVerticesShader, const char * pathToFragmentShader, bool isPath)
//{
//    std::string paths = std::string(pathToVerticesShader) + std::string(pathToFragmentShader);
//    std::hash<std::string> hash;
//    size_t key = hash(paths);
//    if (m_shaderPrograms.find(key) == m_shaderPrograms.end())
//    {
//        if (!createShaderProgram(pathToVerticesShader, pathToFragmentShader, isPath))
//        {
//            return nullptr;
//        }
//    }

//    return m_shaderPrograms[key];
//}

//bool ResourceManager::hasShader(const char * path, bool isPath)
//{
//    std::string key = std::string(path);
//    if (m_shaders.find(key) == m_shaders.end())
//    {
//        return false;
//    }
//    return true;
//}

//bool ResourceManager::createShader(const char * pathOrText, const ShaderType & type, bool isPath)
//{
//    std::string key = std::string(pathOrText);
//    std::string text;

//    if (isPath)
//    {
//        std::ifstream file;

//        file.open(pathOrText);

//        if (!file.good())
//        {
//            std::cout << "Failed to open file: " << pathOrText << std::endl;
//            return false;
//        }

//        std::stringstream stream;
//        stream << file.rdbuf();
//        file.close();

//        text = stream.str();
//    }
//    else
//    {
//        text = pathOrText;
//    }

//    std::shared_ptr<Shader> shader = std::make_shared<Shader>(text.c_str(), type);
//    if (!shader->compile())
//    {
//        std::cout << "Can't compile shader!" << std::endl;
//        return false;
//    }

//    m_shaders[key] = shader;
//    return true;
//}

//std::shared_ptr<Shader> ResourceManager::getShader(const char * path, bool isPath)
//{
//    std::string key = std::string(path);
//    if (m_shaders.find(key) == m_shaders.end())
//    {
//        return nullptr;
//    }

//    return m_shaders[key];
//}

std::shared_ptr<Shader> createShaderFromFile(const char * pathToFile, ShaderType type)
{
    std::ifstream file;

    file.open(pathToFile);

    if (!file.good())
    {
        throw std::invalid_argument("Failed to open file: " + std::string(pathToFile));
    }

    std::stringstream stream;
    stream << file.rdbuf();
    file.close();

    std::string text;
    text = stream.str();

    std::shared_ptr<Shader> shader = std::make_shared<Shader>(text.c_str(), type);
    if (!shader->compile())
    {
        std::cout << "Can't compile shader!" << std::endl;
        throw std::invalid_argument("Can't compile shader: " + std::string(pathToFile));
    }
    return shader;
}

}
