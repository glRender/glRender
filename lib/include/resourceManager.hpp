#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "base.h"

#include "shader.hpp"
#include "shaderProgram.hpp"

#include "texture.hpp"
#include "textures.hpp"

namespace glRender {

template<typename T, typename Parent>
class ResourceCache
{
public:
    template<typename ... Args>
    std::shared_ptr<T> create(std::size_t hashId, Args... args)
    {
        return std::move(static_cast<Parent*>(this)->create(hashId, args...));
    }

    template<typename T0>
    std::size_t hash(T0 p0)
    {
        return std::hash<std::string>{}(p0);
    }

    template<typename T0, typename T1>
    std::size_t hash(T0 p0, T1 p1)
    {
        return hash(p0) + hash(p1);
    }

    template<typename T0, typename T1, typename T2>
    std::size_t hash(T0 p0, T1 p1, T2 p2)
    {
        return hash(p0, p1) + hash(p2);
    }

    template<typename ... Args>
    std::shared_ptr<T> get(const char * id, Args&&... args)
    {
        std::string id_s(id);
        std::size_t hashId = hash(id_s) + hash(std::forward<Args>(args)...);
        if (m_resources.find(hashId) == m_resources.end() && m_resources[hashId].expired() == true)
        {
            return std::move(create(hashId, std::forward<Args>(args)...));
        }

        return m_resources[hashId].lock();
    }

protected:
    std::unordered_map<std::size_t, std::weak_ptr<T>> m_resources;
};

class TextureCache : public ResourceCache<Texture, TextureCache>
{
public:
    std::shared_ptr<Texture> create(std::size_t hashId, const char * path)
    {
        std::shared_ptr<Texture> resourceSharedPtr = std::make_shared<Texture>(path);
        m_resources[hashId] = resourceSharedPtr;
        return std::move(resourceSharedPtr);
    }
};

std::shared_ptr<Shader> createShaderFromFile(const char * pathToFile, ShaderType type);

class ShaderProgramCache : public ResourceCache<ShaderProgram, ShaderProgramCache>
{
public:
    std::shared_ptr<ShaderProgram> create(std::size_t hashId, const char * pathToVerticesShader, const char * pathToFragmentShader)
    {
        std::shared_ptr<ShaderProgram> program = std::make_shared<ShaderProgram>();

        std::map<ShaderType, const char *> pathes = {
            {ShaderType::VertexShader, pathToVerticesShader},
            {ShaderType::FragmentShader, pathToFragmentShader}
        };

        for (auto & i : pathes)
        {
            std::shared_ptr<Shader> shader = createShaderFromFile(i.second, i.first);
            program->attach(i.first, shader);
        }

        if (!program->link())
        {
            throw std::invalid_argument("Failed shaders linkage!");
        }

        m_resources[hashId] = program;
        return std::move(program);
    }
};

class ResourceManager
{    
public:
    static ResourceManager & getInstance()
    {
        static ResourceManager instance; // Guaranteed to be destroyed.
                              // Instantiated on first use.
        return instance;
    }
    ResourceManager(ResourceManager const &) = delete;
    void operator=(ResourceManager const &)  = delete;

    // Note: Scott Meyers mentions in his Effective Modern
    //       C++ book, that deleted functions should generally
    //       be public as it results in better error messages
    //       due to the compilers behavior to check accessibility
    //       before deleted status

public:
//    Texture *       getTexture(const char * path);
//    std::shared_ptr<Shader> getShader(const char * path, bool isPath = true);
//    ShaderProgram * getShaderProgram(const char * pathToVerticesShader, const char * pathToFragmentShader, bool isPath = true);

    inline TextureCache & textures()
    {
        return m_textureCache;
    }

    inline ShaderProgramCache & shaderPrograms()
    {
        return m_shaderProgramsChache;
    }


private:
//    bool hasShader(const char * path, bool isPath = true);
//    bool createShader(const char * path, const ShaderType & type, bool isPath = true);
//    bool            hasShaderProgram(const char * pathToVerticesShader, const char * pathToFragmentShader, bool isPath = true);
//    bool            createShaderProgram(const char * pathToVerticesShader, const char * pathToFragmentShader, bool isPath = true);
    ResourceManager() {}                    // Constructor? (the {} brackets) are needed here.

    // C++ 11
    // =======
    // We can use the better technique of deleting the methods
    // we don't want.

//    std::map<std::string, Texture *> m_textures;
//    std::map<size_t, ShaderProgram *> m_shaderPrograms;
//    std::map<std::string, std::shared_ptr<Shader>> m_shaders;

    TextureCache m_textureCache;
    ShaderProgramCache m_shaderProgramsChache;

};

}

#endif // RESOURCEMANAGER_H
