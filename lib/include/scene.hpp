#ifndef __SCENE_HPP__		
#define __SCENE_HPP__

#include "base.h"

#include "node.hpp"
#include "visitor.hpp"

namespace glRender
{

class Scene
{
    
public:
    Scene();
    ~Scene();

    void updateCache();
    void addToCache(Node * node);
    void removeFromCache(Node * node);

    void add(Node * node);
    
    void setCamera(Camera * camera);
    bool hasCamera();
    Camera * camera();

    void traverse(std::function<void(Node * node)> handler);
//    void traverse(std::function<void(IUpdateable * o)> handler);
//    void traverse(std::function<void(IDrawable * o)> handler);
//    void traverse(std::function<void(IIntersectable * o)> handler);

//    std::vector<Node *> query(std::function<bool(const Node * node)> condition);
//    std::vector<IUpdateable *> query(std::function<bool(IUpdateable * o)> condition);
//    std::vector<IDrawable *> query(std::function<bool(IDrawable * o)> condition);
    std::vector<IIntersectable *> query(std::function<bool (const IIntersectable * o)> condition) const;

    void drawFrame();
    void update();

private:
    std::vector<Node * > m_childs;
    Camera * m_camera = nullptr;

    std::unordered_map<void *, IBaseUpdateable *> m_updateables;
    std::unordered_map<void *, IBaseDrawable *> m_drawables;
    std::unordered_map<void *, IIntersectable *> m_intersectables;
};

}

#endif /* __SCENE_HPP__ */
