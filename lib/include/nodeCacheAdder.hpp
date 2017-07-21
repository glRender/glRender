#pragma once

#include "base.h"
#include "visitor.hpp"

namespace glRender
{

template<typename...> class NodeMixedWith;
class NodeCache;

class NodeCacheAdder : public NodeVisitor
{
public:
    NodeCacheAdder(NodeCache & cache);

    void visit(NodeMixedWith<IUpdateable> * ref) override;
    void visit(NodeMixedWith<IUpdateable, IDrawable> * ref) override;
    void visit(NodeMixedWith<IUpdateable, IDrawable, IIntersectable> * ref) override;
    void visit(NodeMixedWith<IUpdateable, IDrawable, IIntersectable, IKeyPressable> * ref) override;
    void visit(NodeMixedWith<IUpdateable, IKeyPressable> * ref) override;
    void visit(NodeMixedWith<IUpdateable, IDrawable, IKeyPressable> * ref) override;
    void visit(NodeMixedWith<IUpdateable, IIntersectable, IKeyPressable> *ref) override;
    void visit(NodeMixedWith<IDrawable, IKeyPressable, IIntersectable> *ref) override;
    void visit(NodeMixedWith<IUpdateable, IIntersectable> *ref) override;
    void visit(NodeMixedWith<IDrawable, IIntersectable> *ref) override;
    void visit(NodeMixedWith<IDrawable, IKeyPressable> *ref) override;
    void visit(NodeMixedWith<IIntersectable, IKeyPressable> *ref) override;
    void visit(NodeMixedWith<IDrawable> *ref) override;
    void visit(NodeMixedWith<IIntersectable> *ref) override;
    void visit(NodeMixedWith<IKeyPressable> *ref) override;

private:
    NodeCache & cache;
};

}
