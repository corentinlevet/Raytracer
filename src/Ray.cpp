/*
** EPITECH PROJECT, 2022
** Ray.cpp
** File description:
** Source file for the Ray class
*/

#include "Ray.hpp"

#include "HitRecord.hpp"
#include "FormList.hpp"

/* Constructors and destructors */

RayTracer::Ray::Ray(const RayTracer::Math::Point3D &origin, const RayTracer::Math::Vector3D &direction, const double time) : _origin(origin), _direction(direction), _time(time) {}

RayTracer::Ray::Ray(const RayTracer::Ray &other) : _origin(other._origin), _direction(other._direction), _time(other._time) {}

RayTracer::Ray::Ray(RayTracer::Ray &&other) : _origin(other._origin), _direction(other._direction), _time(other._time) {}

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

RayTracer::Math::Color RayTracer::Ray::rayColor(const RayTracer::Ray &ray, const RayTracer::Math::Color &background, const RayTracer::Forms::FormList &world, int depth) const
{
    RayTracer::Forms::HitRecord record;

    if (depth <= 0)
        return RayTracer::Math::Color(0, 0, 0);

    if (!world.hit(ray, 0.001, infinity, record))
        return background;

    if (record.getMaterial() == nullptr) {
        RayTracer::Math::Vector3D normal(record.getNormal());
        RayTracer::Math::Vector3D vectorPoint(record.getPoint().getX(), record.getPoint().getY(), record.getPoint().getZ());

        RayTracer::Math::Vector3D target = vectorPoint + normal + Math::Vector3D::randomUnitVector();

        return rayColor(RayTracer::Ray(record.getPoint(), target - vectorPoint), background, world, depth - 1) * 0.5;
    }

    RayTracer::Ray scattered;
    RayTracer::Math::Color attenuation;
    RayTracer::Math::Color emitted = record.getMaterial()->emitted(record.getU(), record.getV(), record.getPoint());

    if (!record.getMaterial()->scatter(ray, record, attenuation, scattered))
        return emitted;

    return emitted + attenuation * rayColor(scattered, background, world, depth - 1);
}
