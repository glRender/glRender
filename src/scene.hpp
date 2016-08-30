#ifndef __SCENE_HPP__		
#define __SCENE_HPP__

#include "base.h"
#include "node.hpp"

namespace glRender
{

class Scene
{
    
public:
    Scene();
    ~Scene();

    bool addNode(Node * node);
    
    void setActiveCamera(Camera * camera);
	bool hasActiveCamera();
    Camera * activeCamera();

    void traverse(std::function<void(Node * node)> handler);
    void draw();
    void update();

private:
    std::vector<Node * > _nodes;
    Camera * _activeCamera = nullptr;
};

}

#endif /* __SCENE_HPP__ */
