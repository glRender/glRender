#pragma once

#include "base.h"
#include "nodeMixer.hpp"

namespace glRender
{

class NodeCache
{
public:
    std::list<Node *> nodes;
    std::list<IUpdateable *> updateables;
    std::list<IDrawable *> drawables;
    std::list<IIntersectable *> intersectables;
    std::list<IKeyPressable *> keyPressable;
};


}
