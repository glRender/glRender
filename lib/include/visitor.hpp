#ifndef VISITOR_HPP
#define VISITOR_HPP

#include "base.h"
#include "ray.hpp"
#include "camera.hpp"
#include "node.hpp"

namespace glRender
{

class IDrawable;
class IUpdateable;
class IIntersectable;
class ITransformable;

class Visitor
{
public:
    virtual void visit(IUpdateable * ref) = 0;
    virtual void visit(IDrawable * ref) = 0;
    virtual void visit(IIntersectable * ref) = 0;

    virtual ~Visitor() = default;
};

class IBaseDrawable
{
public:
    virtual void draw(CameraPtr camera) = 0;
};

class IBaseUpdateable
{
public:
    virtual void update() = 0;

    Mat4 & transforms() {
        return m_localTransforms;
    }

private:
    Mat4 m_localTransforms;

};

//class IBaseIntersectable
//{
//public:
//    virtual bool intersects(const Ray * ray) const = 0;
//    virtual IBoundingBox * bb() const = 0;
//    virtual void onIntersection(Ray * ray) = 0;
//    virtual void onIntersection(IIntersectable * o) = 0;
//};

class IUpdateable :
    public Node,
    public IBaseUpdateable
{
public:
    void accept(Visitor & v) override {
        v.visit(this);
    }
};

class IDrawable :
    public Node,
    public IBaseUpdateable,
    public IBaseDrawable
{
public:
    void accept(Visitor & v) override {
        v.visit(this);
    }
};

class IIntersectable :
    public Node,
    public IBaseUpdateable,
    public IBaseDrawable
{
public:
    void accept(Visitor & v) override {
        v.visit(this);
    }

    virtual bool intersects(const RayPtr ray) const = 0;
    virtual IBoundingBox * bb() const = 0;
    virtual void onMouseUp(RayPtr ray, CameraPtr camera) = 0;
    virtual void onMouseDown(RayPtr ray, CameraPtr camera) = 0;
    virtual void onMouseMove(Vec3 & toPosition) = 0;

    virtual void onIntersection(IIntersectable * o) = 0;

};

class CacheNodeAdder : public Visitor
{
public:
    CacheNodeAdder(
        std::unordered_map<void *, IBaseUpdateable *> & updateables,
        std::unordered_map<void *, IBaseDrawable *> & drawables,
        std::unordered_map<void *, IIntersectable *> & intersectables) :
        m_updateables(updateables),
        m_drawables(drawables),
        m_intersectables(intersectables)
    {
    }

    void visit(IUpdateable * ref) override {
        m_updateables[ref] = ref;
    }
    
    void visit(IDrawable * ref) override {
        m_updateables[ref] = ref;
        m_drawables[ref] = ref;
    }

    void visit(IIntersectable *ref) override {
        m_updateables[ref] = ref;
        m_drawables[ref] = ref;
        m_intersectables[ref] = ref;
    }
    
private:
    std::unordered_map<void *, IBaseUpdateable *> & m_updateables;
    std::unordered_map<void *, IBaseDrawable *> & m_drawables;
    std::unordered_map<void *, IIntersectable *> & m_intersectables;

};

class CacheNodeRemover : public Visitor
{
public:
    CacheNodeRemover(
        std::unordered_map<void *, IBaseUpdateable *> & updateables,
        std::unordered_map<void *, IBaseDrawable *> & drawables,
        std::unordered_map<void *, IIntersectable *> & intersectables) :
        m_updateables(updateables),
        m_drawables(drawables),
        m_intersectables(intersectables)
    {
    }

    void visit(IUpdateable * ref) override {
        if (m_updateables.find(ref) != m_updateables.end())
        {
            m_updateables.erase(ref);
        }
    }

    void visit(IDrawable * ref) override {
        if (m_updateables.find(ref) != m_updateables.end())
        {
            m_updateables.erase(ref);
        }
        if (m_drawables.find(ref) != m_drawables.end())
        {
            m_drawables.erase(ref);
        }
    }

    void visit(IIntersectable *ref) override {
        if (m_updateables.find(ref) != m_updateables.end())
        {
            m_updateables.erase(ref);
        }
        if (m_drawables.find(ref) != m_drawables.end())
        {
            m_drawables.erase(ref);
        }
        if (m_intersectables.find(ref) != m_intersectables.end())
        {
            m_intersectables.erase(ref);
        }
    }

private:
    std::unordered_map<void *, IBaseUpdateable *> & m_updateables;
    std::unordered_map<void *, IBaseDrawable *> & m_drawables;
    std::unordered_map<void *, IIntersectable *> & m_intersectables;

};

class TransformsAccumulator : public Visitor
{
public:
    TransformsAccumulator(Mat4 & m) :
        m_m(m)
    {
    }

    void visit(IUpdateable * ref) override {
        m_m *= ref->transforms();
    }

    void visit(IDrawable * ref) override {
        m_m *= ref->transforms();
    }

    void visit(IIntersectable *ref) override {
        m_m *= ref->transforms();
    }

private:
    Mat4 & m_m;

};

}

#endif
