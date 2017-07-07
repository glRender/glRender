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

    Vec3 coordOnDistance(Vec2 normDeviceCoords, float distance);
    RayPtr ray(Vec2 normDeviceCoords);

    std::vector<IIntersectable *> findAll(float x, float y); /**< Find all nodes which impliments interface IIntersectable under mouse pointer */
    std::vector<IIntersectable *> findAll(Vec2 normDeviceCoords); /**< Find all nodes which impliments interface IIntersectable under mouse pointer */
    IIntersectable * findNearest(float nx, float ny);
    IIntersectable * findNearest(Vec2 normDeviceCoords);
    void mouseDownUnderNearest(float nx, float ny);
    void mouseDownUnderNearest(Vec2 normDeviceCoords);
    void mouseUpUnderNearest(float nx, float ny);
    void mouseUpUnderNearest(Vec2 normDeviceCoords);
    void mouseMoveUnderNearest(float nx, float ny);
    void mouseMoveUnderNearest(Vec2 normDeviceCoords);

private:
    Vec2 changeCoordSystemOfNormolizedDeviceCoords(float nx, float ny);

private:
    Camera * m_camera = nullptr;
    Scene * m_scene = nullptr;

    IIntersectable * m_pressedNearestNode = nullptr;
};

using NodePickerPtr = std::shared_ptr<NodePicker>;

}

#endif /* __NODEPICKER_HPP__ */
