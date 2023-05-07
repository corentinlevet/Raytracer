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
    Math::Vector3D oc(ray.getOrigin().getX() - _center.getX(), ray.getOrigin().getY() - _center.getY(), ray.getOrigin().getZ() - _center.getZ());
    double a = dot(ray.getDirection(), ray.getDirection());
    double b = 2.0 * dot(oc, ray.getDirection());
    double c = dot(oc, oc) - _radius * _radius;
    double delta = b * b - 4 * a * c;
    return (delta > 0);
}
