#include "scene.hpp"

namespace glRender {

Scene::Scene()
{

}

Scene::~Scene()
{

}

bool Scene::addNode(Node * node)
{
	_nodes.push_back(node);
	return true;
}

void Scene::setActiveCamera(Camera * camera)
{
	_activeCamera = camera;
}

bool Scene::hasActiveCamera()
{
	return _activeCamera != nullptr;
}

Camera * Scene::activeCamera()
{
	return _activeCamera;
}

void Scene::traverse(std::function<void(Node * node)> handler)
{
	for (Node * node : _nodes)
	{
		node->traverse(handler);
	}	
}

void Scene::draw()
{
	traverse([=](Node * node) {
		node->draw(activeCamera());
	});
}

void Scene::update()
{
	traverse([=](Node * node) {
		node->update();
	});
}

}