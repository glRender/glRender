#pragma once

#include "base.h"
#include "nodeCache.hpp"
#include "eventManager.hpp"

namespace glRender
{

class NodeCacheAdder;
class NodeCacheRemover;
class Node;

class Scene
{
public:
    Scene();
    virtual ~Scene();

    void addToCache(Node * node);
    void removeFromCache(Node * node);

    void add(Node * node);
    
    void setCamera(Camera * camera);
    bool hasCamera();
    Camera * camera();

    void traverse(std::function<void(Node *)> handler);
    void traverse(std::function<void(IUpdateable *)> handler);
    void traverse(std::function<void(IDrawable *)> handler);
    void traverse(std::function<void(IIntersectable *)> handler);
    void traverse(std::function<void(IKeyPressable *)> handler);

    std::vector<Node *>           query(std::function<bool(const Node *)> condition);
    std::vector<IUpdateable *>    query(std::function<bool(const IUpdateable *)> condition);
    std::vector<IDrawable *>      query(std::function<bool(const IDrawable *)> condition);
    std::vector<IIntersectable *> query(std::function<bool(const IIntersectable *)> condition);
    std::vector<IKeyPressable *>  query(std::function<bool(const IKeyPressable *)> condition);

    void drawFrame();
    void update();
    void processKeyboardsKeys(IKeyPressable::KeyboardKey key);

protected:
    enum class Event
    {
        PrevDraw,
        AfterDraw
    };

    EventManager<Scene::Event> & eventManager();
private:
    std::vector<Node * > m_childs;
    Camera * m_camera = nullptr;

    NodeCache m_cache;
    EventManager<Scene::Event> m_eventManager;
};

}
