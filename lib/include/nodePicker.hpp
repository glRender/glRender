#ifndef __NODEPICKER_HPP__
#define __NODEPICKER_HPP__

#include "base.h"
#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"
#include "mat4.hpp"
#include "ray.hpp"
#include "node.hpp"
#include "scene.hpp"
#include "camera.hpp"

namespace glRender
{
class NodePicker
{
public:
    NodePicker(Camera * camera, Scene * scene)
        : m_camera(camera)
        , m_scene(scene)
    {

    }

    template <class T>
    std::vector<T *> find(Vec2 normDeviceCoords)
    {
        Vec4 clipCoords(
                    normDeviceCoords.x,
                    normDeviceCoords.y,
                    -1.0f,
                    1.0f );

        Mat4 p = m_camera->projectionMatrix();
        p.invert();
        Vec4 eyeCoords = p * clipCoords;
        eyeCoords.z = -1.0f;
        eyeCoords.w = 0.0f;

        Mat4 t = m_camera->transformationMatrix();
        t.invert();
        Vec4 tmp = t * eyeCoords;
        Vec3 worldCoords(tmp.x, tmp.y, tmp.z);
        worldCoords.normalize();

        Vec3 cameraPos = m_camera->position();
        Vec3 origin = cameraPos + worldCoords * m_camera->nearPlane();
        Vec3 target = cameraPos + worldCoords * m_camera->farPlane();

        Ray * ray = new Ray(origin, target);

        std::vector<T *> result;

        m_scene->traverse([ray, &result](Node * node) {
            if (node->isSelectable())
            {
                if (node->bb()->intersects(ray))
                {
                    T * c = dynamic_cast<T *>(node);
                    if (c != nullptr)
                    {
                        result.push_back(c);
                    }
                }
            }
        });

        delete ray;

        return result;

    }

    template <class T>
    std::vector<T *> find(float x, float y)
    {
        return find<T>(Vec2(x, y));
    }

private:
    Camera * m_camera = nullptr;
    Scene * m_scene = nullptr;

};

}

#endif /* __NODEPICKER_HPP__ */
