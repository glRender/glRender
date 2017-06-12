#include "node.hpp"

#include "visitor.hpp"
#include "camera.hpp"
#include "boundingBox.hpp"
#include "model.hpp"
#include "nodeTransformsAccumulator.hpp"

namespace glRender {

Node::~Node()
{
    for (Node * n : m_childs)
    {
        delete n;
    }
}

void Node::add(Node * node)
{
    node->m_parent = this;
    m_childs.push_back(node);
    notifyUp(Event::ADD, node);
}

std::vector<Node * > & Node::childs()
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
    for (auto & o : m_childs)
	{
        o->traverse(handler);
    }
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

void Node::subscribeTo(Node::Event event, std::function<void (Node *)> handler)
{
    eventHandlers[event] = handler;
}

Mat4 Node::parentsTransforms()
{
    Mat4 result;
    NodeTransformsAccumulator v(result);
    Node * p = parent();

    while (p != nullptr)
    {
        p->accept(&v);
        p = p->parent();
    }
    return result;
}

void Node::notifyUp(Node::Event event, Node *node)
{
    if (m_parent != nullptr)
    {
        m_parent->notifyUp(event, node);
    }

    if (eventHandlers.find(event) != eventHandlers.end())
    {
        eventHandlers[event](node);
    }

}

}
