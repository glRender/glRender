#include "node.hpp"

namespace glRender {

Node::~Node()
{
    for (Node * n : m_childs)
    {
        delete n;
    }
}

bool Node::addChild(Node * node)
{
	m_childs.push_back( node );
	return true;
}

std::vector<Node * > Node::childs()
{
	return m_childs;
}

Node * Node::parent()
{
    return m_parent;
}

void Node::traverse(std::function<void(Node * node)> handler)
{
	handler(this);
    for (uint32_t i=0; i<m_childs.size(); i++)
	{
		traverse(handler);
    }
}

void Node::setOrigin(const Vec3 & pos)
{
    model()->setOrigin(pos);
    bb()->setOrigin(pos);
}

void Node::setOrigin(float x, float y, float z)
{
    setOrigin(Vec3(x, y, z));
}

void Node::setSelectable(bool isSelectable)
{
    m_isSelectable = isSelectable;
}

bool Node::isSelectable()
{
    return m_isSelectable;
}

}
