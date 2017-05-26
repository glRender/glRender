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
    NodePicker(CameraPtr camera, Scene * scene)
        : m_camera(camera)
        , m_scene(scene)
    {

    }

    Vec3 coordOnDistance(Vec2 normDeviceCoords, float distance)
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

        return m_camera->position() + worldCoords * distance;
    }

    RayPtr ray(Vec2 normDeviceCoords)
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

        Vec3 origin = coordOnDistance(normDeviceCoords, m_camera->nearPlane());
        Vec3 target = coordOnDistance(normDeviceCoords, m_camera->farPlane());

        return RayPtr(new Ray(origin, target));
    }

    template <class T>
    std::vector<T *> find(Vec2 normDeviceCoords)
    {
        RayPtr ray = this->ray(normDeviceCoords);

        std::vector<T *> result;

//        m_scene->traverse([ray, &result](IBaseIntersectable * o) {
//            if (node->isSelectable())
//            {
//                if (node->bb()->intersects(ray))
//                {
//                    T * c = dynamic_cast<T *>(node);
//                    if (c != nullptr)
//                    {
//                        result.push_back(c);
//                    }
//                }
//            }
//            if (o->isIntersected(ray))
//            {
//                result.push_back(o);
//            }

//        });

        return result;

    }

    template <class T>
    std::vector<T *> find(float x, float y)
    {
        return find<T>(Vec2(x, y));
    }

private:
    CameraPtr m_camera = nullptr;
    Scene * m_scene = nullptr;

};

using NodePickerPtr = std::shared_ptr<NodePicker>;

}

#endif /* __NODEPICKER_HPP__ */
