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

    Node()
    {
    }

    virtual ~Node();
    virtual void accept(NodeVisitor * v) = 0;

    void add(Node * node);
    void remove(Node * node);

    std::list<Node *> & childs();
    Node * parent() const;

    void traverse(std::function<void(Node * node)> handler);
    std::vector<Node *> query(std::function<bool(const Node * node)> condition);

    void subscribeTo(Event event, std::function<void(Node * node)> handler);

    const Mat4 parentsTransforms();

    void transformsChanged();
    Mat4 & transforms();
    const Mat4 & globalTransforms();

    bool isParentsTransformsChanged() const;

private:
    void notifyUp(Event event, Node * node);
    void updateGlobalTransforms();

private:
    Node * m_parent = nullptr;
    std::list<Node * > m_childs;

    Mat4 m_localTransforms;
    Mat4 m_globalTransforms;

    bool m_transformsChanged = true;
    std::map<Event, std::function<void(Node * node)>> eventHandlers;

};

}
