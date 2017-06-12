#pragma once

#include "base.h"
#include "mat4.hpp"

namespace glRender
{
class NodeVisitor;
class IBoundingBox;
class Model;

class Node
{
public:
    enum class Event
    {
        ADD,
        REMOVE
    };

    virtual ~Node();
    virtual void accept(NodeVisitor * v) = 0;

    void add(Node * node);
    std::vector<Node *> & childs();
    Node * parent();

    void traverse(std::function<void(Node * node)> handler);
    std::vector<Node *> query(std::function<bool(const Node * node)> condition);

    void subscribeTo(Event event, std::function<void(Node * node)> handler);

    Mat4 parentsTransforms();

private:
    void notifyUp(Event event, Node * node);

private:
    Node * m_parent = nullptr;
    std::vector<Node * > m_childs;
    Mat4 m_transforms;
    std::map<Event, std::function<void(Node * node)>> eventHandlers;

};

}
