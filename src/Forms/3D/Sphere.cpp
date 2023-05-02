/*
** EPITECH PROJECT, 2022
** Sphere.cpp
** File description:
** Source file for the Sphere class
*/

#include "Sphere.hpp"

extern "C"
{
    std::unique_ptr<RayTracer::Forms::IForm> entryPoint()
    {
        return std::make_unique<RayTracer::Forms::Sphere>();
    }
}

/* Constructor */

RayTracer::Forms::Sphere::Sphere(double radius, const RayTracer::Math::Point3D &center) : _radius(radius), _center(center)
{
    _type = "Sphere";
}

/* Getters and setters */

double RayTracer::Forms::Sphere::getRadius() const
{
    return _radius;
}

RayTracer::Math::Point3D RayTracer::Forms::Sphere::getCenter() const
{
    return _center;
}

void RayTracer::Forms::Sphere::setRadius(double radius)
{
    _radius = radius;
}

void RayTracer::Forms::Sphere::setCenter(const RayTracer::Math::Point3D &center)
{
    _center = center;
}

/* Methods */

bool RayTracer::Forms::Sphere::hits(const RayTracer::Ray &ray) const
{
    Math::Vector3D oc(ray._origin._x - _center._x, ray._origin._y - _center._y, ray._origin._z - _center._z);

    double a = ray._direction.dot(ray._direction);
    double b = 2 * ray._direction.dot(oc);
    double c = oc.dot(oc) - _radius * _radius;
    double delta = b * b - 4 * a * c;

    return delta >= 0;
}
