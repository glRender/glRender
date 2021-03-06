#pragma once

#include "base.h"

#include "node.hpp"
#include "camera.hpp"
#include "mat4.hpp"
#include "visitor.hpp"

namespace glRender
{

template<typename...> class NodeMixedWith;

class IDrawable
{
public:
    virtual void draw(Camera * camera) = 0;
};

class IUpdateable
{
public:
    virtual void update() = 0;
};

class IIntersectable
{
public:
    virtual bool intersects(const RayPtr ray) const = 0;
    virtual const IBoundingBox * bb() const = 0;
    virtual void onMouseUp(Vec3 & position, RayPtr ray, Camera * camera) = 0;
    virtual void onMouseDown(Vec3 & position, RayPtr ray, Camera * camera) = 0;
    virtual void onMouseMove(Vec3 & toPosition) = 0;
//    virtual void onIntersection(NodeMixedWith<IUpdateable, IDrawable, IIntersectable> * o) = 0;
};

class IMouseListenable
{
public:
    virtual void onMouseUp(Vec2 normDeviceCoords, RayPtr ray, Camera *) = 0;
    virtual void onMouseDown(Vec2 normDeviceCoords, RayPtr ray, Camera *) = 0;
    virtual void onMouseMove(Vec2 normDeviceCoords, RayPtr ray, Camera *) = 0;
};

class IKeyPressable
{
public:
    enum class KeyboardKey
    {
        Q,
        W,
        E,
        R,
        T,
        A,
        S,
        D,
        F,
        G,
        Z,
        X,
        C,
        V
    };

    virtual void onKeyPress(KeyboardKey key) = 0;
};

template<typename T0>
class NodeMixedWith<T0> :
        public Node,
        public T0
{
public:
    void accept(NodeVisitor * v) {
        v->visit(this);
    }

};

template<typename T0, typename T1>
class NodeMixedWith<T0, T1> :
        public Node,
        public T0,
        public T1
{
public:
    virtual void accept(NodeVisitor * v) {
        v->visit(this);
    }

};

template<typename T0, typename T1, typename T2>
class NodeMixedWith<T0, T1, T2> :
        public Node,
        public T0,
        public T1,
        public T2
{
public:
    virtual void accept(NodeVisitor * v) {
        v->visit(this);
    }

};

template<typename T0, typename T1, typename T2, typename T3>
class NodeMixedWith<T0, T1, T2, T3> :
        public Node,
        public T0,
        public T1,
        public T2,
        public T3
{
public:
    virtual void accept(NodeVisitor * v) {
        v->visit(this);
    }

};

}
