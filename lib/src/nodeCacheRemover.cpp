#include "nodeCacheRemover.hpp"

namespace glRender {

NodeCacheRemover::NodeCacheRemover(NodeCache &cache) :
    cache(cache)
{
}

void NodeCacheRemover::visit(NodeMixedWith<IUpdateable> *ref) {

    cache.updateables.remove(ref);
    cache.nodes.remove(ref);
}

void NodeCacheRemover::visit(NodeMixedWith<IUpdateable, IDrawable> *ref) {
    cache.updateables.remove(ref);
    cache.drawables.remove(ref);
    cache.nodes.remove(ref);
}

void NodeCacheRemover::visit(NodeMixedWith<IUpdateable, IDrawable, IIntersectable> *ref) {
    cache.updateables.remove(ref);
    cache.drawables.remove(ref);
    cache.intersectables.remove(ref);
    cache.nodes.remove(ref);
}

void NodeCacheRemover::visit(NodeMixedWith<IUpdateable, IDrawable, IIntersectable, IKeyPressable> *ref) {
    cache.updateables.remove(ref);
    cache.drawables.remove(ref);
    cache.intersectables.remove(ref);
    cache.keyPressable.remove(ref);
    cache.nodes.remove(ref);
}

void NodeCacheRemover::visit(NodeMixedWith<IUpdateable, IKeyPressable> *ref) {
    cache.updateables.remove(ref);
    cache.keyPressable.remove(ref);
    cache.nodes.remove(ref);
}

void NodeCacheRemover::visit(NodeMixedWith<IUpdateable, IDrawable, IKeyPressable> *ref) {
    cache.updateables.remove(ref);
    cache.drawables.remove(ref);
    cache.keyPressable.remove(ref);
    cache.nodes.remove(ref);
}

void NodeCacheRemover::visit(NodeMixedWith<IUpdateable, IIntersectable, IKeyPressable> *ref) {
    cache.updateables.remove(ref);
    cache.intersectables.remove(ref);
    cache.keyPressable.remove(ref);
    cache.nodes.remove(ref);
}

void NodeCacheRemover::visit(NodeMixedWith<IDrawable, IKeyPressable, IIntersectable> *ref) {
    cache.drawables.remove(ref);
    cache.intersectables.remove(ref);
    cache.keyPressable.remove(ref);
    cache.nodes.remove(ref);
}

void NodeCacheRemover::visit(NodeMixedWith<IUpdateable, IIntersectable> *ref) {
    cache.updateables.remove(ref);
    cache.intersectables.remove(ref);
    cache.nodes.remove(ref);
}

void NodeCacheRemover::visit(NodeMixedWith<IDrawable, IIntersectable> *ref) {
    cache.drawables.remove(ref);
    cache.intersectables.remove(ref);
    cache.nodes.remove(ref);
}

void NodeCacheRemover::visit(NodeMixedWith<IDrawable, IKeyPressable> *ref) {
    cache.drawables.remove(ref);
    cache.keyPressable.remove(ref);
    cache.nodes.remove(ref);
}

void NodeCacheRemover::visit(NodeMixedWith<IIntersectable, IKeyPressable> *ref) {
    cache.intersectables.remove(ref);
    cache.keyPressable.remove(ref);
    cache.nodes.remove(ref);
}

void NodeCacheRemover::visit(NodeMixedWith<IDrawable> *ref) {
    cache.drawables.remove(ref);
    cache.nodes.remove(ref);
}

void NodeCacheRemover::visit(NodeMixedWith<IIntersectable> *ref) {
    cache.intersectables.remove(ref);
    cache.nodes.remove(ref);
}

void NodeCacheRemover::visit(NodeMixedWith<IKeyPressable> *ref) {
    cache.keyPressable.remove(ref);
    cache.nodes.remove(ref);
}

}
