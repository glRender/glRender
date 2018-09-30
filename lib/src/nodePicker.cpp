#include "nodePicker.hpp"

#include "boundingBox.hpp"
#include "scene.hpp"
#include "camera.hpp"
#include "node.hpp"
#include "ray.hpp"

using namespace glRender;

Vec3 NodePicker::coordOnDistance(const Vec2 & normDeviceCoords, float distance)
{
    Vec2 coords = changeCoordSystemOfNormolizedDeviceCoords(normDeviceCoords.x, normDeviceCoords.y);

    Vec4 clipCoords(
                coords.x,
                coords.y,
                -1.0f,
                1.0f );

    Mat4 p = m_camera->projectionMatrix();
    p.invert();
    Vec4 eyeCoords = p * clipCoords;
    eyeCoords.z = -1.0f;
    eyeCoords.w = 0.0f;

    Mat4 t = m_camera->globalMatrix();
    t.invert();
    Vec4 tmp = t * eyeCoords;
    Vec3 worldCoords(tmp.x, tmp.y, tmp.z);
    worldCoords.normalize();

    return m_camera->position() + worldCoords * distance;
}

RayPtr NodePicker::ray(const Vec2 & normDeviceCoords)
{
    Vec2 coords = changeCoordSystemOfNormolizedDeviceCoords(normDeviceCoords.x, normDeviceCoords.y);

    Vec4 clipCoords(
                coords.x,
                coords.y,
                -1.0f,
                1.0f );

    Mat4 p = m_camera->projectionMatrix();
    p.invert();
    Vec4 eyeCoords = p * clipCoords;
    eyeCoords.z = -1.0f;
    eyeCoords.w = 0.0f;

    Mat4 t = m_camera->globalMatrix();
    t.invert();
    Vec4 tmp = t * eyeCoords;
    Vec3 worldCoords(tmp.x, tmp.y, tmp.z);
    worldCoords.normalize();

    Vec3 origin = coordOnDistance(normDeviceCoords, m_camera->nearPlane());
    Vec3 target = coordOnDistance(normDeviceCoords, m_camera->farPlane());

    return std::make_shared<Ray>(origin, target);
}

IIntersectable * NodePicker::findNearest(float nx, float ny)
{
    return findNearest(Vec2(nx, ny));
}

IIntersectable * NodePicker::findNearest(const Vec2 & normDeviceCoords)
{
    auto nodes = findAll(normDeviceCoords);

    IIntersectable * nearestNode = nullptr;
    float nearestNodeDistance = 2 * m_camera->farPlane();

    for (auto & node : nodes)
    {
        float distance = node->bb()->origin().distance(m_camera->position());
        if (distance < nearestNodeDistance)
        {
            nearestNode = node;
            nearestNodeDistance = distance;
        }
    }

    m_pressedNearestNode = nearestNode;

    return nearestNode;
}

void NodePicker::mouseDownUnderNearest(float nx, float ny)
{
    mouseDownUnderNearest(Vec2(nx, ny));
}

void NodePicker::mouseDownUnderNearest(const Vec2 & normDeviceCoords)
{
    m_pressedNearestNode = findNearest(normDeviceCoords);
    if (m_pressedNearestNode)
    {
        float pressedNodeDistance = m_pressedNearestNode->bb()->origin().distance(m_camera->position());
        auto pos = coordOnDistance(normDeviceCoords, pressedNodeDistance);
        auto ray = this->ray(normDeviceCoords);
        m_pressedNearestNode->onMouseDown(pos, ray, m_camera);
    }
}

void NodePicker::mouseUpUnderNearest(float nx, float ny)
{
    mouseUpUnderNearest(Vec2(nx, ny));
}

void NodePicker::mouseUpUnderNearest(const Vec2 & normDeviceCoords)
{
    if (m_pressedNearestNode)
    {
        float pressedNodeDistance = m_pressedNearestNode->bb()->origin().distance(m_camera->position());
        auto pos = coordOnDistance(normDeviceCoords, pressedNodeDistance);
        auto ray = this->ray(normDeviceCoords);
        m_pressedNearestNode->onMouseUp(pos, ray, m_camera);
    }
}

void NodePicker::mouseMoveUnderNearest(float nx, float ny)
{
    mouseMoveUnderNearest(Vec2(nx, ny));
}

void NodePicker::mouseMoveUnderNearest(const Vec2 & normDeviceCoords)
{
    if (m_pressedNearestNode)
    {
        float pressedNodeDistance = m_pressedNearestNode->bb()->origin().distance(m_camera->position());
        Vec3 newPos = coordOnDistance(normDeviceCoords, pressedNodeDistance);
        m_pressedNearestNode->onMouseMove(newPos);
    }

}

std::vector<IIntersectable *> NodePicker::findAll(float nx, float ny)
{
    return findAll(Vec2(nx, ny));
}

std::vector<IIntersectable *> NodePicker::findAll(const Vec2 & normDeviceCoords)
{
    auto ray = this->ray(normDeviceCoords);

    std::vector<IIntersectable *> result = m_scene->queryIntersectables([ray](const IIntersectable * o) {
        return o->intersects(ray);
    });

    return result;
}

Vec2 NodePicker::changeCoordSystemOfNormolizedDeviceCoords(float nx, float ny)
{
    return Vec2(2.0f * nx - 1.0f, 1.0f - 2.0f * ny );
}
