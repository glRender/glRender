#include "node.hpp"

namespace glRender {

Node::Node()
{
//    m_bb = new AABB(Vec3(0,0,0), 1.0);
}

//Node::~Node()
//{
//    delete m_bb;
//}

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
