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

    void visit(NodeMixedWith<IUpdateable> * pointer) override;
    void visit(NodeMixedWith<IUpdateable, IDrawable> * pointer) override;
    void visit(NodeMixedWith<IUpdateable, IDrawable, IIntersectable> * pointer) override;
    void visit(NodeMixedWith<IUpdateable, IDrawable, IIntersectable, IKeyPressable> * pointer) override;
    void visit(NodeMixedWith<IUpdateable, IKeyPressable> * pointer) override;
    void visit(NodeMixedWith<IUpdateable, IDrawable, IKeyPressable> * pointer) override;
    void visit(NodeMixedWith<IUpdateable, IIntersectable, IKeyPressable> *pointer) override;
    void visit(NodeMixedWith<IDrawable, IKeyPressable, IIntersectable> *pointer) override;
    void visit(NodeMixedWith<IUpdateable, IIntersectable> *pointer) override;
    void visit(NodeMixedWith<IDrawable, IIntersectable> *pointer) override;
    void visit(NodeMixedWith<IDrawable, IKeyPressable> *pointer) override;
    void visit(NodeMixedWith<IIntersectable, IKeyPressable> *pointer) override;
    void visit(NodeMixedWith<IDrawable> *pointer) override;
    void visit(NodeMixedWith<IIntersectable> *pointer) override;
    void visit(NodeMixedWith<IKeyPressable> *pointer) override;

private:
    NodeCache & cache;
};

}
