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

    void add(Node * node);
    void remove(Node * node);
    
    void setCamera(Camera * camera);
    bool hasCamera();
    Camera * camera() const;

    std::vector<Node *>           queryNodes         (std::function<bool(const Node *          )> condition);
    std::vector<IUpdateable *>    queryUpdateables   (std::function<bool(const IUpdateable *   )> condition);
    std::vector<IDrawable *>      queryDrawables     (std::function<bool(const IDrawable *     )> condition);
    std::vector<IIntersectable *> queryIntersectables(std::function<bool(const IIntersectable *)> condition);
    std::vector<IKeyPressable *>  queryKeyPressables (std::function<bool(const IKeyPressable * )> condition);

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
    void addToCache(Node * node);
    void removeFromCache(Node * node);
    void traverseNodes(std::function<void(Node *)> handler);
    void traverseUpdateables(std::function<void(IUpdateable *)> handler);
    void traverseDrawables(std::function<void(IDrawable *)> handler);
    void traverseIntersectables(std::function<void(IIntersectable *)> handler);
    void traverseKeyPressables(std::function<void(IKeyPressable *)> handler);

private:
    std::list<Node * > m_childs;
    Camera * m_camera = nullptr;

    NodeCache m_cache;
    EventManager<Scene::Event> m_eventManager;
};

}
