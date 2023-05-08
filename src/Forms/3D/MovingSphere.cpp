/*
** EPITECH PROJECT, 2022
** MovingSphere.cpp
** File description:
** Source file for the MovingSphere class
*/

#include "MovingSphere.hpp"

#include "HitRecord.hpp"
#include "Ray.hpp"

extern "C"
{
    FormPtr entryPointForm()
    {
        return std::make_unique<RayTracer::Forms::MovingSphere>();
    }
}

/* Constructor */

RayTracer::Forms::MovingSphere::MovingSphere(const double radius, const double time0, const double time1, const RayTracer::Math::Point3D &center0, const RayTracer::Math::Point3D &center1, const std::shared_ptr<RayTracer::Materials::IMaterial> &material) : _radius(radius), _time0(time0), _time1(time1), _center0(center0), _center1(center1)
{
    _material = material;
    _name = "MovingSphere";
}

/* Getters and setters */

double RayTracer::Forms::MovingSphere::getRadius() const
{
    return _radius;
}

double RayTracer::Forms::MovingSphere::getTime0() const
{
    return _time0;
}

double RayTracer::Forms::MovingSphere::getTime1() const
{
    return _time1;
}

RayTracer::Math::Point3D RayTracer::Forms::MovingSphere::getCenter0() const
{
    return _center0;
}

RayTracer::Math::Point3D RayTracer::Forms::MovingSphere::getCenter1() const
{
    return _center1;
}

void RayTracer::Forms::MovingSphere::setRadius(double radius)
{
    _radius = radius;
}

void RayTracer::Forms::MovingSphere::setTime0(double time0)
{
    _time0 = time0;
}

void RayTracer::Forms::MovingSphere::setTime1(double time1)
{
    _time1 = time1;
}

void RayTracer::Forms::MovingSphere::setCenter0(const RayTracer::Math::Point3D &center0)
{
    _center0 = center0;
}

void RayTracer::Forms::MovingSphere::setCenter1(const RayTracer::Math::Point3D &center1)
{
    _center1 = center1;
}

/* Methods */

bool RayTracer::Forms::MovingSphere::hits(const RayTracer::Ray &ray, double t_min, double t_max, HitRecord &hitRecord) const
{
    Math::Vector3D oc(ray.getOrigin().getX() - center(ray.getTime()).getX(), ray.getOrigin().getY() - center(ray.getTime()).getY(), ray.getOrigin().getZ() - center(ray.getTime()).getZ());
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
    Math::Point3D outwardNormal = (hitRecord.getPoint() - center(ray.getTime())) / _radius;
    Math::Vector3D outwardNormalVector(outwardNormal.getX(), outwardNormal.getY(), outwardNormal.getZ());
    hitRecord.setFaceNormal(ray, outwardNormalVector);
    hitRecord.setMaterial(_material);

    return true;
}

RayTracer::Math::Point3D RayTracer::Forms::MovingSphere::center(double time) const
{
    return _center0 + ((time - _time0) / (_time1 - _time0)) * (_center1 - _center0);
}
