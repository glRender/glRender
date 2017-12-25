#pragma once

#include "glRender.h"

namespace glRender {

class Camera;

class Label : public NodeMixedWith<IUpdateable, IDrawable>
{
public:
    Label(Camera * camera, std::shared_ptr<Font::Font> font, const std::string & text);

    void update() override;
    void draw(Camera * camera) override;
    void setText(const std::string & text);

    std::shared_ptr<Model> model();

private:
    Camera * m_camera;
    std::shared_ptr<LabelModel> m_label;
};

}