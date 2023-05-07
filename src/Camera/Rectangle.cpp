/*
** EPITECH PROJECT, 2022
** Rectangle.cpp
** File description:
** Source file for the Rectangle class
*/

#include "Rectangle.hpp"

/* Constructors and destructors */

RayTracer::Camera::Rectangle::Rectangle(const Math::Point3D &origin, const Math::Vector3D &bottomSide, const Math::Vector3D &leftSide) : _origin(origin), _bottomSide(bottomSide), _leftSide(leftSide) {}

/* Getters and setters */

const RayTracer::Math::Point3D &RayTracer::Camera::Rectangle::getOrigin() const
{
    return _origin;
}

const RayTracer::Math::Vector3D &RayTracer::Camera::Rectangle::getHorizontal() const
{
    return _bottomSide;
}

const RayTracer::Math::Vector3D &RayTracer::Camera::Rectangle::getVertical() const
{
    return _leftSide;
}

void RayTracer::Camera::Rectangle::setOrigin(const RayTracer::Math::Point3D &origin)
{
    _origin = origin;
}

void RayTracer::Camera::Rectangle::setBottomSide(const RayTracer::Math::Vector3D &bottomSide)
{
    _bottomSide = bottomSide;
}

void RayTracer::Camera::Rectangle::setLeftSide(const RayTracer::Math::Vector3D &leftSide)
{
    _leftSide = leftSide;
}

/* Methods */

RayTracer::Math::Point3D RayTracer::Camera::Rectangle::pointAt(double u, double v) const
{
    if (u < 0 || u > 1 || v < 0 || v > 1)
        throw softError("pointAt", "u and v must be between 0 and 1");

    RayTracer::Math::Point3D point(_origin);

    point += _bottomSide * u;
    point += _leftSide * v;

    return point;
}
