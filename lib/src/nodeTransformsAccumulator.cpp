#include "nodeTransformsAccumulator.hpp"

namespace glRender {

NodeTransformsAccumulator::NodeTransformsAccumulator(Mat4 &m) :
    m_m(m)
{
}

void NodeTransformsAccumulator::visit(NodeMixedWith<IUpdateable> *ref)
{
    accumulate(ref);
}

void NodeTransformsAccumulator::visit(NodeMixedWith<IUpdateable, IDrawable> *ref)
{
    accumulate(ref);
}

void NodeTransformsAccumulator::visit(NodeMixedWith<IUpdateable, IDrawable, IIntersectable> *ref)
{
    accumulate(ref);
}

void NodeTransformsAccumulator::visit(NodeMixedWith<IUpdateable, IDrawable, IIntersectable, IKeyPressable> *ref)
{
    accumulate(ref);
}

void NodeTransformsAccumulator::visit(NodeMixedWith<IUpdateable, IKeyPressable> *ref)
{
    accumulate(ref);
}

void NodeTransformsAccumulator::visit(NodeMixedWith<IUpdateable, IDrawable, IKeyPressable> *ref)
{
    accumulate(ref);
}

void NodeTransformsAccumulator::visit(NodeMixedWith<IUpdateable, IIntersectable, IKeyPressable> *ref)
{
    accumulate(ref);
}

void NodeTransformsAccumulator::visit(NodeMixedWith<IDrawable, IKeyPressable, IIntersectable> *ref)
{

}

void NodeTransformsAccumulator::visit(NodeMixedWith<IUpdateable, IIntersectable> *ref)
{
    accumulate(ref);
}

void NodeTransformsAccumulator::visit(NodeMixedWith<IDrawable, IIntersectable> *ref)
{

}

void NodeTransformsAccumulator::visit(NodeMixedWith<IDrawable, IKeyPressable> *ref)
{

}

void NodeTransformsAccumulator::visit(NodeMixedWith<IIntersectable, IKeyPressable> *ref)
{

}

void NodeTransformsAccumulator::visit(NodeMixedWith<IDrawable> *ref)
{

}

void NodeTransformsAccumulator::visit(NodeMixedWith<IIntersectable> *ref)
{

}

void NodeTransformsAccumulator::visit(NodeMixedWith<IKeyPressable> *ref)
{

}

void NodeTransformsAccumulator::accumulate(IUpdateable * ref)
{
    m_m *= ref->transforms();
}

}
