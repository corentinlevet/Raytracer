/*
** EPITECH PROJECT, 2022
** Camera.cpp
** File description:
** Source file for the Camera class
*/

#include "Camera.hpp"

/* Constructors and destructors */

RayTracer::Camera::Camera::Camera(const Math::Point3D &origin, const RayTracer::Camera::Rectangle &rectangle) : _origin(origin), _rectangle(rectangle) {}

/* Getters and setters */

const RayTracer::Math::Point3D &RayTracer::Camera::Camera::getOrigin() const
{
    return _origin;
}

const RayTracer::Camera::Rectangle &RayTracer::Camera::Camera::getRectangle() const
{
    return _rectangle;
}

void RayTracer::Camera::Camera::setOrigin(const RayTracer::Math::Point3D &origin)
{
    _origin = origin;
}

void RayTracer::Camera::Camera::setRectangle(const RayTracer::Camera::Rectangle &rectangle)
{
    _rectangle = rectangle;
}

/* Methods */

RayTracer::Ray RayTracer::Camera::Camera::ray(double u, double v) const
{
    Math::Point3D point = _rectangle.pointAt(u, v);
    Math::Vector3D direction(point._x - _origin._x, point._y - _origin._y, point._z - _origin._z);

    return Ray(_origin, direction);
}
