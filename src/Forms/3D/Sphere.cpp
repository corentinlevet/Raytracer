/*
** EPITECH PROJECT, 2022
** Sphere.cpp
** File description:
** Source file for the Sphere class
*/

#include "Sphere.hpp"

#include "HitRecord.hpp"
#include "Ray.hpp"

extern "C"
{
    std::shared_ptr<RayTracer::Forms::IForm> entryPoint()
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

bool RayTracer::Forms::Sphere::hits(const RayTracer::Ray &ray, double t_min, double t_max, HitRecord &hitRecord) const
{
    Math::Vector3D oc(ray.getOrigin().getX() - _center.getX(), ray.getOrigin().getY() - _center.getY(), ray.getOrigin().getZ() - _center.getZ());
    double a = ray.getDirection().lengthSquared();
    double half_b = dot(oc, ray.getDirection());
    double c = oc.lengthSquared() - _radius * _radius;
    double delta = half_b * half_b - a * c;

    if (delta < 0)
        return false;
    double sqrtd = sqrt(delta);
    double root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    hitRecord.setT(root);
    hitRecord.setPoint(ray.pointAt(hitRecord.getT()));
    Math::Point3D outwardNormal = (hitRecord.getPoint() - _center) / _radius;
    Math::Vector3D outwardNormalVector(outwardNormal.getX(), outwardNormal.getY(), outwardNormal.getZ());
    hitRecord.setFaceNormal(ray, outwardNormalVector);

    return true;
}
