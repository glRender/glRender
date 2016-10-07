#include "node.hpp"

namespace glRender {

Node::Node()
{

}

// Node::~Node()
// {

// }

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
	for (Node * node : m_childs)
	{
		traverse(handler);
	}	
}

}
