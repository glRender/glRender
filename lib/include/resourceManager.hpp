#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "base.h"

#include "shader.hpp"
#include "shaderProgram.hpp"

#include "texture.hpp"
#include "textures.hpp"

namespace glRender {

// template CRPT
template<typename T, typename Parent>
class ResourceCache
{
public:
    template<typename ... Args>
    std::shared_ptr<T> create(std::size_t hashId, Args... args)
    {
        return std::move(static_cast<Parent*>(this)->create(hashId, args...));
    }

    template<typename ... Args>
    std::shared_ptr<T> get(const char * id, Args&&... args)
    {
        std::string id_s(id);
        std::size_t hashId = patch::hash(id_s) + patch::hash(std::forward<Args>(args)...);
        if (m_resources.find(hashId) == m_resources.end() && m_resources[hashId].expired() == true)
        {
            return std::move(create(hashId, std::forward<Args>(args)...));
        }

        return m_resources[hashId].lock();
    }

protected:
    std::unordered_map<std::size_t, std::weak_ptr<T>> m_resources;
};

// template CRPT (curious recoursive ... template)
// I use it for reload method template method ResourceCache::create
class TextureCache : public ResourceCache<Texture, TextureCache>
{
public:
    std::shared_ptr<Texture> create(std::size_t hashId, const char * path)
    {
        std::shared_ptr<Texture> resourceSharedPtr = createTextureFromFile(path);
        m_resources[hashId] = resourceSharedPtr;
        return std::move(resourceSharedPtr);
    }
};

// template CRPT (curious recoursive ... template)
// I use it for reload method template method ResourceCache::create
class ShaderProgramCache : public ResourceCache<ShaderProgram, ShaderProgramCache>
{
public:
    std::shared_ptr<ShaderProgram> create(std::size_t hashId, const char * pathToVerticesShader, const char * pathToFragmentShader)
    {
        std::map<ShaderType, const char *> pathes = {
            {ShaderType::VertexShader, pathToVerticesShader},
            {ShaderType::FragmentShader, pathToFragmentShader}
        };
        std::shared_ptr<ShaderProgram> program = createShaderProgramFromFiles(pathes);
        m_resources[hashId] = program;
        return std::move(program);
    }
};

class ResourceManager
{    
public:
    static ResourceManager & getInstance()
    {
        static ResourceManager instance;
        return instance;
    }
    ResourceManager(ResourceManager const &) = delete;
    void operator=(ResourceManager const &)  = delete;

public:
    inline TextureCache & textures()
    {
        return m_textureCache;
    }

    inline ShaderProgramCache & shaderPrograms()
    {
        return m_shaderProgramsChache;
    }

private:
    ResourceManager() {}

    TextureCache m_textureCache;
    ShaderProgramCache m_shaderProgramsChache;
};

}

#endif // RESOURCEMANAGER_H
