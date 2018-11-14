#include "nodeCacheAdder.hpp"

#include "nodeCache.hpp"
#include "nodeMixer.hpp"

using namespace glRender;

NodeCacheAdder::NodeCacheAdder(NodeCache &cache) :
    cache(cache)
{
}

void NodeCacheAdder::visit(NodeMixedWith<IUpdateable> *ref) {
    cache.updateables.push_back(ref);
    cache.nodes.push_back(ref);
}

void NodeCacheAdder::visit(NodeMixedWith<IUpdateable, IDrawable> *ref) {
    cache.updateables.push_back(ref);
    cache.drawables.push_back(ref);
    cache.nodes.push_back(ref);
}

void NodeCacheAdder::visit(NodeMixedWith<IUpdateable, IDrawable, IIntersectable> *ref) {
    cache.updateables.push_back(ref);
    cache.drawables.push_back(ref);
    cache.intersectables.push_back(ref);
    cache.nodes.push_back(ref);
}

void NodeCacheAdder::visit(NodeMixedWith<IUpdateable, IDrawable, IIntersectable, IKeyPressable> *ref) {
    cache.updateables.push_back(ref);
    cache.drawables.push_back(ref);
    cache.intersectables.push_back(ref);
    cache.keyPressable.push_back(ref);
    cache.nodes.push_back(ref);
}

void NodeCacheAdder::visit(NodeMixedWith<IUpdateable, IKeyPressable> *ref) {
    cache.updateables.push_back(ref);
    cache.keyPressable.push_back(ref);
    cache.nodes.push_back(ref);
}

void NodeCacheAdder::visit(NodeMixedWith<IUpdateable, IDrawable, IKeyPressable> *ref) {
    cache.updateables.push_back(ref);
    cache.drawables.push_back(ref);
    cache.keyPressable.push_back(ref);
    cache.nodes.push_back(ref);
}

void NodeCacheAdder::visit(NodeMixedWith<IUpdateable, IIntersectable, IKeyPressable> *ref) {
    cache.updateables.push_back(ref);
    cache.intersectables.push_back(ref);
    cache.keyPressable.push_back(ref);
    cache.nodes.push_back(ref);
}

void NodeCacheAdder::visit(NodeMixedWith<IDrawable, IKeyPressable, IIntersectable> *ref) {
    cache.drawables.push_back(ref);
    cache.intersectables.push_back(ref);
    cache.keyPressable.push_back(ref);
    cache.nodes.push_back(ref);
}

void NodeCacheAdder::visit(NodeMixedWith<IUpdateable, IIntersectable> *ref) {
    cache.updateables.push_back(ref);
    cache.intersectables.push_back(ref);
    cache.nodes.push_back(ref);
}

void NodeCacheAdder::visit(NodeMixedWith<IDrawable, IIntersectable> *ref) {
    cache.drawables.push_back(ref);
    cache.intersectables.push_back(ref);
    cache.nodes.push_back(ref);
}

void NodeCacheAdder::visit(NodeMixedWith<IDrawable, IKeyPressable> *ref) {
    cache.drawables.push_back(ref);
    cache.keyPressable.push_back(ref);
    cache.nodes.push_back(ref);
}

void NodeCacheAdder::visit(NodeMixedWith<IIntersectable, IKeyPressable> *ref) {
    cache.intersectables.push_back(ref);
    cache.keyPressable.push_back(ref);
    cache.nodes.push_back(ref);
}

void NodeCacheAdder::visit(NodeMixedWith<IDrawable> *ref) {
    cache.drawables.push_back(ref);
    cache.nodes.push_back(ref);
}

void NodeCacheAdder::visit(NodeMixedWith<IIntersectable> *ref) {
    cache.intersectables.push_back(ref);
    cache.nodes.push_back(ref);
}

void NodeCacheAdder::visit(NodeMixedWith<IKeyPressable> *ref) {
    cache.keyPressable.push_back(ref);
    cache.nodes.push_back(ref);
}

void glRender::NodeCacheAdder::visit(NodeMixedWith<glRender::IMouseListenable> *ref)
{
    cache.mouseListenable.push_back(ref);
    cache.nodes.push_back(ref);
}

void glRender::NodeCacheAdder::visit(NodeMixedWith<glRender::IUpdateable, glRender::IKeyPressable, glRender::IMouseListenable> *ref)
{
    cache.mouseListenable.push_back(ref);
    cache.keyPressable.push_back(ref);
    cache.nodes.push_back(ref);
}
