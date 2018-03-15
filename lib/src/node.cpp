#include "node.hpp"

#include "visitor.hpp"
#include "camera.hpp"
#include "boundingBox.hpp"
#include "model.hpp"
#include "nodeTransformsAccumulator.hpp"

namespace glRender {

Node::~Node()
{
    for (auto & n : m_childs)
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

void Node::remove(Node * node)
{
    m_childs.remove(node);
    node->m_parent = nullptr;
    notifyUp(Event::REMOVE, node);
}

std::list<Node *> & Node::childs()
{
    return m_childs;
}

Node * Node::parent() const
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

std::vector<Node *> Node::query(std::function<bool (const Node *)> condition)
{
    std::vector<Node *> result;
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

const Mat4 Node::parentsTransforms()
{
    if (m_parent)
    {
        if (m_parent->m_transformsChanged == true)
        {
            return m_parent->parentsTransforms() * m_parent->m_localTransforms;
        }
        return m_parent->m_globalTransforms;
    }
    return Mat4();
}

const Mat4 & Node::globalTransforms()
{
    if (m_transformsChanged)
    {
        updateGlobalTransforms();
    }
    return m_globalTransforms;
}

bool Node::isParentsTransformsChanged() const
{
    return m_transformsChanged;
}

//void Node::setParentsTransformsChanged(bool updated)
//{
//    m_parentsTransformsChanged = updated;
//}

void Node::updateGlobalTransforms()
{
    m_globalTransforms = parentsTransforms() * m_localTransforms;
    m_transformsChanged = false;
}

Mat4 & Node::transforms()
{
    return m_localTransforms;
}

void Node::transformsChanged()
{
//    m_parentsTransforms = parentsTransforms() * m_localTransforms;
    m_transformsChanged = true;
    traverse([](Node * node) {
        node->m_transformsChanged = true;
    });
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
