/*
** EPITECH PROJECT, 2022
** Ray.cpp
** File description:
** Source file for the Ray class
*/

#include "Ray.hpp"

#include "HitRecord.hpp"

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

/* Public methods */

RayTracer::Math::Point3D RayTracer::Ray::pointAt(double t) const
{
    RayTracer::Math::Point3D point(_origin);
    point += _direction * t;
    return point;
}

RayTracer::Math::Color RayTracer::Ray::rayColor(const RayTracer::Forms::FormList &world) const
{
    RayTracer::Forms::HitRecord record;
    if (world.hit(*this, 0, infinity, record)) {
        RayTracer::Math::Color color(record.getNormal().getX() + 1, record.getNormal().getY() + 1, record.getNormal().getZ() + 1);
        return color * 0.5;
    }
    RayTracer::Math::Vector3D unitDirection = unitVector(_direction);
    double t = 0.5 * (unitDirection.getY() + 1.0);
    return RayTracer::Math::Color(1.0, 1.0, 1.0) * (1.0 - t) + RayTracer::Math::Color(0.5, 0.7, 1.0) * t;
}
