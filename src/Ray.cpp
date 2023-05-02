/*
** EPITECH PROJECT, 2022
** Ray.cpp
** File description:
** Source file for the Ray class
*/

#include "Ray.hpp"

/* Constructors and destructors */

RayTracer::Ray::Ray(const RayTracer::Math::Point3D &origin, const RayTracer::Math::Vector3D &direction) : _origin(origin), _direction(direction) {}

RayTracer::Ray::Ray(const RayTracer::Ray &other) : _origin(other._origin), _direction(other._direction) {}

RayTracer::Ray::Ray(RayTracer::Ray &&other) : _origin(other._origin), _direction(other._direction) {}

/* Operators */

RayTracer::Ray &RayTracer::Ray::operator=(const RayTracer::Ray &other)
{
    _origin = other._origin;
    _direction = other._direction;
    return *this;
}

RayTracer::Ray &RayTracer::Ray::operator=(RayTracer::Ray &&other)
{
    _origin = other._origin;
    _direction = other._direction;
    return *this;
}
