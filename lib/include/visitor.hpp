#ifndef VISITOR_HPP
#define VISITOR_HPP

#include "base.h"
#include "ray.hpp"
#include "camera.hpp"

namespace glRender
{

class IDrawable;
class IUpdateable;
class IIntersectable;
class IKeyPressable;

template<typename...> class NodeMixedWith;

class NodeVisitor
{
public:
    virtual void visit(NodeMixedWith<IUpdateable> * pointer) = 0;
    virtual void visit(NodeMixedWith<IUpdateable, IDrawable> * pointer) = 0;
    virtual void visit(NodeMixedWith<IUpdateable, IDrawable, IIntersectable> * pointer) = 0;
    virtual void visit(NodeMixedWith<IUpdateable, IDrawable, IIntersectable, IKeyPressable> * pointer) = 0;
    virtual void visit(NodeMixedWith<IUpdateable, IKeyPressable> * pointer) = 0;
    virtual void visit(NodeMixedWith<IUpdateable, IDrawable, IKeyPressable> * pointer) = 0;
    virtual void visit(NodeMixedWith<IUpdateable, IIntersectable, IKeyPressable> *pointer) = 0;
    virtual void visit(NodeMixedWith<IDrawable, IKeyPressable, IIntersectable> *pointer) = 0;
    virtual void visit(NodeMixedWith<IUpdateable, IIntersectable> *pointer) = 0;
    virtual void visit(NodeMixedWith<IDrawable, IIntersectable> *pointer) = 0;
    virtual void visit(NodeMixedWith<IDrawable, IKeyPressable> *pointer) = 0;
    virtual void visit(NodeMixedWith<IIntersectable, IKeyPressable> *pointer) = 0;
    virtual void visit(NodeMixedWith<IDrawable> *pointer) = 0;
    virtual void visit(NodeMixedWith<IIntersectable> *pointer) = 0;
    virtual void visit(NodeMixedWith<IKeyPressable> *pointer) = 0;
};

}

#endif
