#include "labelNode.hpp"

#include "camera.hpp"

namespace glRender {

LabelNode::LabelNode(Camera * camera, std::shared_ptr<Font::Font> font, const std::string & text) :
    m_camera(camera)
{
    m_label = std::make_shared<Label>(font, text);
}

void LabelNode::update()
{
    static int counter = 0;
    // if (counter % 50 == 0)
    {
        // std::string t = patch::to_string(((rand() % 999999999999999999)) - 25);
        std::string t = patch::to_string(counter);
        setText(t);
    }
    counter++;
}

void LabelNode::draw(Camera * camera)
{
    m_label->setParentsMatrix(globalTransforms());
    m_label->draw(camera);
}


void LabelNode::setText(const std::string & text)
{
    m_label->setText(text);
}

std::shared_ptr<Model> LabelNode::model()
{
    return m_label;
}

}