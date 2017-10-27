#pragma once

#include "base.h"
#include "vec3.hpp"
#include "vec2.hpp"

namespace glRender
{

class Camera;
class Scene;
class IIntersectable;
class Node;
class Ray;

class NodePicker
{
public:
    NodePicker(Camera * camera, Scene * scene)
        : m_camera(camera)
        , m_scene(scene)
    {

    }

    Vec3 coordOnDistance(const Vec2 & normDeviceCoords, float distance);
    std::shared_ptr<Ray> ray(const Vec2 & normDeviceCoords);

    std::vector<IIntersectable *> findAll(float x, float y); /**< Find all nodes which impliments interface IIntersectable under mouse pointer */
    std::vector<IIntersectable *> findAll(const Vec2 & normDeviceCoords); /**< Find all nodes which impliments interface IIntersectable under mouse pointer */
    IIntersectable * findNearest(float nx, float ny);
    IIntersectable * findNearest(const Vec2 & normDeviceCoords);
    void mouseDownUnderNearest(float nx, float ny);
    void mouseDownUnderNearest(const Vec2 & normDeviceCoords);
    void mouseUpUnderNearest(float nx, float ny);
    void mouseUpUnderNearest(const Vec2 & normDeviceCoords);
    void mouseMoveUnderNearest(float nx, float ny);
    void mouseMoveUnderNearest(const Vec2 & normDeviceCoords);

private:
    Vec2 changeCoordSystemOfNormolizedDeviceCoords(float nx, float ny);

private:
    Camera * m_camera = nullptr;
    Scene * m_scene = nullptr;
    IIntersectable * m_pressedNearestNode = nullptr;
};

using NodePickerPtr = std::shared_ptr<NodePicker>;

}
