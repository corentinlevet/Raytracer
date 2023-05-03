/*
** EPITECH PROJECT, 2022
** Camera.cpp
** File description:
** Source file for the Camera class
*/

#include "Camera.hpp"

#include <iostream>

/* Constructors and destructors */

RayTracer::Camera::Camera::Camera(const Math::Point3D &origin, const RayTracer::Camera::Rectangle &rectangle, std::tuple<int, int> resolution, std::tuple<int, int, int> rotation, double fov) : _origin(origin), _screen(rectangle), _resolution(resolution), _rotation(rotation), _fov(fov) {}

/* Getters and setters */

const RayTracer::Math::Point3D &RayTracer::Camera::Camera::getOrigin() const
{
    return _origin;
}

const RayTracer::Camera::Rectangle &RayTracer::Camera::Camera::getScreen() const
{
    return _screen;
}

void RayTracer::Camera::Camera::setOrigin(const RayTracer::Math::Point3D &origin)
{
    _origin = origin;
}

void RayTracer::Camera::Camera::setScreen(const RayTracer::Camera::Rectangle &rectangle)
{
    _screen = rectangle;
}

/* Methods */

RayTracer::Ray RayTracer::Camera::Camera::ray(double u, double v) const
{
    Math::Point3D point = _screen.pointAt(u, v);
    Math::Vector3D direction(point._x - _origin._x, point._y - _origin._y, point._z - _origin._z);

    return Ray(_origin, direction);
}
