#include "label.hpp"

#include "camera.hpp"

namespace glRender {

Label::Label(Camera * camera, std::shared_ptr<Font::Font> font, const std::string & text)
{
    m_label = std::make_shared<LabelModel>(font, text);
}

void Label::update()
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

void Label::draw(Camera * camera)
{
    m_label->setParentsMatrix(globalTransforms());
    m_label->draw(camera);
}


void Label::setText(const std::string & text)
{
    m_label->setText(text);
}

std::shared_ptr<Model> Label::model()
{
    return m_label;
}

}