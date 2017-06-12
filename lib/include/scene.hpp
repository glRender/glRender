#pragma once

#include "base.h"
#include "nodeCache.hpp"

namespace glRender
{

class NodeCacheAdder;
class NodeCacheRemover;
class Node;

class Scene
{
    
public:
    Scene();
    ~Scene();

    void addToCache(Node * node);
    void removeFromCache(Node * node);

    void add(Node * node);
    
    void setCamera(CameraPtr camera);
    bool hasCamera();
    CameraPtr camera();

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

private:
    std::vector<Node * > m_childs;
    CameraPtr m_camera = nullptr;

    NodeCache m_cache;
};

}
