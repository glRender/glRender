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

bool Node::isSelectable() const
{
    return m_isSelectable;
}

std::vector<glRender::Node *> glRender::Node::query(std::function<bool (const glRender::Node *)> condition)
{
    std::vector<glRender::Node *> result;
    for (auto node : m_childs)
    {
        auto sample = node->query(condition);
        result.insert(result.end(), sample.begin(), sample.end());
    }

    if (condition(this))
    {
        result.push_back(this);
    }

    return result;

}

}
