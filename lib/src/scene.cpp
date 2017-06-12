#include "scene.hpp"

#include "node.hpp"
#include "nodeCacheAdder.hpp"
#include "nodeCacheRemover.hpp"

namespace glRender {

Scene::Scene()
{

}

Scene::~Scene()
{

}

void Scene::addToCache(Node * node)
{
    NodeCacheAdder v(m_cache);
    node->accept(&v);
    node->traverse([&v](Node * node) {
        node->accept(&v);
    });
}

void Scene::removeFromCache(Node * node)
{
    NodeCacheRemover v(m_cache);
    node->traverse([&v](Node * node) {
        node->accept(&v);
    });
}

void Scene::add(Node * node)
{
    m_childs.push_back(node);
    node->subscribeTo(Node::Event::ADD, [this](Node * node) {
        addToCache(node);
    });

    node->subscribeTo(Node::Event::REMOVE, [this](Node * node) {
        removeFromCache(node);
    });

    addToCache(node);
}

void Scene::setCamera(CameraPtr camera)
{
    m_camera = camera;
}

bool Scene::hasCamera()
{
    return m_camera != nullptr;
}

CameraPtr Scene::camera()
{
    return m_camera;
}

void Scene::traverse(std::function<void(Node * node)> handler)
{
    for (auto & o : m_cache.nodes)
    {
        handler(o);
    }
}

void Scene::traverse(std::function<void (IUpdateable *)> handler)
{
    for (auto & o : m_cache.updateables)
    {
        handler(o);
    }
}

void Scene::traverse(std::function<void (IDrawable *)> handler)
{
    for (auto & o : m_cache.drawables)
    {
        handler(o);
    }
}

void Scene::traverse(std::function<void (IIntersectable *)> handler)
{
    for (auto & o : m_cache.intersectables)
    {
        handler(o);
    }
}

void Scene::traverse(std::function<void (IKeyPressable *)> handler)
{
    for (auto & o : m_cache.keyPressable)
    {
        handler(o);
    }
}

std::vector<Node *> Scene::query(std::function<bool (const Node *)> condition)
{
    std::vector<Node *> result;
    for (auto & o : m_cache.nodes)
    {
        if (condition(o))
        {
            result.push_back(o);
        }
    }
    return result;
}

std::vector<IUpdateable *> Scene::query(std::function<bool (const IUpdateable *)> condition)
{
    std::vector<IUpdateable *> result;
    for (auto & o : m_cache.updateables)
    {
        if (condition(o))
        {
            result.push_back(o);
        }
    }
    return result;
}

std::vector<IDrawable *> Scene::query(std::function<bool (const IDrawable *)> condition)
{
    std::vector<IDrawable *> result;
    for (auto & o : m_cache.drawables)
    {
        if (condition(o))
        {
            result.push_back(o);
        }
    }
    return result;
}

std::vector<IIntersectable *> Scene::query(std::function<bool (const IIntersectable *)> condition)
{
    std::vector<IIntersectable *> result;
    for (auto & o : m_cache.intersectables)
    {
        if (condition(o))
        {
            result.push_back(o);
        }
    }
    return result;
}

std::vector<IKeyPressable *> Scene::query(std::function<bool (const IKeyPressable *)> condition)
{
    std::vector<IKeyPressable *> result;
    for (auto & o : m_cache.keyPressable)
    {
        if (condition(o))
        {
            result.push_back(o);
        }
    }
    return result;
}

void Scene::drawFrame()
{
    for (const auto & node : m_cache.drawables)
    {
        node->draw(camera());
    }
}

void Scene::update()
{
    for (const auto & node : m_cache.updateables)
    {
        node->update();
    }
}

}
