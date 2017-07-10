#pragma once

#include "base.h"

namespace glRender
{

template <typename T>
class EventManager
{
public:
    void setHandler(T e, std::function<void(void)> f)
    {
        m_eventHandlers[e] = f;
    }

    bool hasHandler(T e)
    {
        return m_eventHandlers.find(e) != m_eventHandlers.end();
    }

    void emitEvent(T e)
    {
        if (m_eventHandlers.find(e) != m_eventHandlers.end())
        {
            m_eventHandlers[e]();
        }
    }

private:
    std::map<T, std::function<void(void)> > m_eventHandlers;

};

}
