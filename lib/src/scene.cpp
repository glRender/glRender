#include "scene.hpp"

#include "node.hpp"
#include "nodeCacheAdder.hpp"
#include "nodeCacheRemover.hpp"
#include "opengl.h"

using namespace glRender;

Scene::Scene()
{
}

Scene::~Scene()
{
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

void Scene::remove(Node * node)
{
    m_childs.remove(node);
    removeFromCache(node);
}

void Scene::setCamera(Camera * camera)
{
    m_camera = camera;
}

bool Scene::hasCamera()
{
    return m_camera != nullptr;
}

Camera * Scene::camera() const
{
    return m_camera;
}

EventManager<Scene::Event> &Scene::eventManager()
{
    return m_eventManager;
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

void Scene::traverseNodes(std::function<void(Node * node)> handler)
{
    for (auto & o : m_cache.nodes)
    {
        handler(o);
    }
}

void Scene::traverseUpdateables(std::function<void (IUpdateable *)> handler)
{
    for (auto & o : m_cache.updateables)
    {
        handler(o);
    }
}

void Scene::traverseDrawables(std::function<void (IDrawable *)> handler)
{
    for (auto & o : m_cache.drawables)
    {
        handler(o);
    }
}

void Scene::traverseIntersectables(std::function<void (IIntersectable *)> handler)
{
    for (auto & o : m_cache.intersectables)
    {
        handler(o);
    }
}

void Scene::traverseKeyPressables(std::function<void (IKeyPressable *)> handler)
{
    for (auto & o : m_cache.keyPressable)
    {
        handler(o);
    }
}

void Scene::traverseMouseListenable(std::function<void (IMouseListenable *)> handler)
{
    for (auto & o : m_cache.mouseListenable)
    {
        handler(o);
    }
}

std::vector<Node *> Scene::queryNodes(std::function<bool (const Node *)> condition)
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

std::vector<IUpdateable *> Scene::queryUpdateables(std::function<bool (const IUpdateable *)> condition)
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

std::vector<IDrawable *> Scene::queryDrawables(std::function<bool (const IDrawable *)> condition)
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

std::vector<IIntersectable *> Scene::queryIntersectables(std::function<bool (const IIntersectable *)> condition)
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

std::vector<IKeyPressable *> Scene::queryKeyPressables(std::function<bool (const IKeyPressable *)> condition)
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

std::vector<IMouseListenable *> glRender::Scene::queryMouseListenable(std::function<bool (const IMouseListenable *)> condition)
{
    std::vector<IMouseListenable *> result;
    for (auto & o : m_cache.mouseListenable)
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
    m_eventManager.emitEvent(Scene::Event::PrevDraw);
    for (const auto & node : m_cache.drawables)
    {
        node->draw(m_camera);
    }
    m_eventManager.emitEvent(Scene::Event::AfterDraw);
}

void Scene::update()
{
    for (const auto & node : m_cache.updateables)
    {
        node->update();
    }
}

void Scene::processKeyboardsKeys(IKeyPressable::KeyboardKey key)
{
    traverseKeyPressables([&key](IKeyPressable * mixin) {
        mixin->onKeyPress(key);
    });
}
