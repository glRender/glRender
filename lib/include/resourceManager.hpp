#pragma once

#include "base.h"

namespace glRender {

class Shader;
class ShaderProgram;
class Texture;
class Textures;

template<typename T>
class ResourceCache
{
public:
    using CreatorCallable = std::function<std::shared_ptr<T>()>;
    std::shared_ptr<T> get(const char * id)
    {
        std::size_t hashId = patch::hash(id);
        if (m_resources.find(hashId) == m_resources.end() && m_resources[hashId].expired() == true)
        {
            if (m_creators.find(hashId) != m_creators.end())
            {
                std::shared_ptr<T> resourceSharedPtr = m_creators[hashId]();
                m_resources[hashId] = resourceSharedPtr;
                return std::move(resourceSharedPtr);
            }
            else
            {
                throw std::invalid_argument("Resource creation failed. No creator for a resource with name " + patch::to_string(id));
            }
        }

        return m_resources[hashId].lock();
    }

    void create(const char * id, CreatorCallable creator)
    {
        m_creators[patch::hash(id)] = creator;
    }

protected:
    std::unordered_map<std::size_t, CreatorCallable> m_creators;
    std::unordered_map<std::size_t, std::weak_ptr<T>> m_resources;
};

class ResourceManager
{    
public:
    static ResourceManager & instance();
    ResourceManager(ResourceManager const &) = delete;
    void operator=(ResourceManager const &)  = delete;

public:
    ResourceCache<Texture> & textures();
    ResourceCache<ShaderProgram> & shaderPrograms();

private:
    ResourceManager();

    ResourceCache<Texture> m_textureCache;
    ResourceCache<ShaderProgram> m_shaderProgramsChache;
};

}
