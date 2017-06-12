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
    virtual void visit(NodeMixedWith<IUpdateable> * ref) = 0;
    virtual void visit(NodeMixedWith<IUpdateable, IDrawable> * ref) = 0;
    virtual void visit(NodeMixedWith<IUpdateable, IDrawable, IIntersectable> * ref) = 0;
    virtual void visit(NodeMixedWith<IUpdateable, IDrawable, IIntersectable, IKeyPressable> * ref) = 0;
    virtual void visit(NodeMixedWith<IUpdateable, IKeyPressable> * ref) = 0;
    virtual void visit(NodeMixedWith<IUpdateable, IDrawable, IKeyPressable> * ref) = 0;
    virtual void visit(NodeMixedWith<IUpdateable, IIntersectable, IKeyPressable> *ref) = 0;
    virtual void visit(NodeMixedWith<IDrawable, IKeyPressable, IIntersectable> *ref) = 0;
    virtual void visit(NodeMixedWith<IUpdateable, IIntersectable> *ref) = 0;
    virtual void visit(NodeMixedWith<IDrawable, IIntersectable> *ref) = 0;
    virtual void visit(NodeMixedWith<IDrawable, IKeyPressable> *ref) = 0;
    virtual void visit(NodeMixedWith<IIntersectable, IKeyPressable> *ref) = 0;
    virtual void visit(NodeMixedWith<IDrawable> *ref) = 0;
    virtual void visit(NodeMixedWith<IIntersectable> *ref) = 0;
    virtual void visit(NodeMixedWith<IKeyPressable> *ref) = 0;
};

}

#endif
