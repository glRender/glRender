#include "orderedScenes.hpp"

using namespace glRender;

void OrderedScenes::add(Scene * scene)
{
    insert(m_orderedScenes.end(), scene);
}

void OrderedScenes::add(Scene * scene, float zIndex)
{
    if (zIndex < 0 || m_orderedScenes.size() == 0)
    {
        insert(m_orderedScenes.begin(), scene);
    }
    else
    {
        uint index = 0;
        for (auto it = m_orderedScenes.begin(); it != m_orderedScenes.end(); it++)
        {
            if (index >= zIndex && index + 1 < zIndex)
            {
                insert(it, scene);
                break;
            }
            index++;
        }
    }
}

std::list<Scene *> OrderedScenes::scenes() const
{
    return m_orderedScenes;
}

void OrderedScenes::insert(std::list<Scene *>::iterator it, Scene * scene)
{
    m_orderedScenes.insert(it, scene);
}
