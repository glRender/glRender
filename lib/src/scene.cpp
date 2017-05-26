#include "scene.hpp"

namespace glRender {

Scene::Scene()
{

}

Scene::~Scene()
{

}

void Scene::updateCache()
{
    CacheNodeAdder v(m_updateables, m_drawables, m_intersectables);
    traverse([&v](Node * node) {
        node->accept(v);
    });
}

void Scene::addToCache(Node * node)
{
    CacheNodeAdder v(m_updateables, m_drawables, m_intersectables);
    node->accept(v);
    node->traverse([&v](Node * node) {
        node->accept(v);
    });
}

void Scene::removeFromCache(Node * p_node)
{
    CacheNodeRemover v(m_updateables, m_drawables, m_intersectables);
    p_node->traverse([&v](Node * node) {
        node->accept(v);
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
    for (Node * node : m_childs)
    {
        node->traverse(handler);
    }
}

void Scene::drawFrame()
{
    for (const auto & node : m_drawables)
    {
        node.second->draw(camera());
    }
}

void Scene::update()
{
    for (const auto & node : m_updateables)
    {
        node.second->update();
    }
}

//std::vector<Node *> Scene::query(std::function<bool (const Node *)> condition)
//{
//    std::vector<glRender::Node *> result;
//    for (auto child : m_childs)
//    {
//        auto sample = child->query(condition);
//        result.insert(result.end(), sample.begin(), sample.end());
//    }
//    return result;
//}

//std::vector<IUpdateable *> Scene::query(std::function<bool (IUpdateable *)> condition)
//{
//    std::vector<IUpdateable *> result;
//    return result;
//}

//std::vector<IDrawable *> Scene::query(std::function<bool (IDrawable *)> condition)
//{
//    std::vector<IDrawable *> result;
//    return result;
//}

std::vector<IIntersectable *> Scene::query(std::function<bool (const IIntersectable * o)> condition) const
{
    std::vector<IIntersectable *> result;
    for (auto & o : m_intersectables)
    {
        if (condition(o.second))
        {
            result.push_back(o.second);
        }
    }
    return result;
}

}
