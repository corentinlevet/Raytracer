/*
** EPITECH PROJECT, 2022
** Sphere.cpp
** File description:
** Source file for the Sphere class
*/

#include "Sphere.hpp"

#include "AxisAlignedBoundingBox.hpp"
#include "HitRecord.hpp"
#include "Ray.hpp"
#include "Utils.hpp"

extern "C"
{
    FormPtr entryPointForm()
    {
        return std::make_unique<RayTracer::Forms::Sphere>();
    }
}

/* Constructor */

RayTracer::Forms::Sphere::Sphere(double radius, const RayTracer::Math::Point3D &center, const std::shared_ptr<RayTracer::Materials::IMaterial> &material) : _radius(radius), _center(center)
{
    _material = material;
    _name = "Sphere";
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
    hitRecord.setMaterial(_material);
    double u = hitRecord.getU(), v = hitRecord.getV();
    getSphereUV(outwardNormal, u, v);
    hitRecord.setU(u); hitRecord.setV(v);

    return true;
}

bool RayTracer::Forms::Sphere::boundingBox(double t0, double t1, AxisAlignedBoundingBox &boundingBox) const
{
    (void)t0; (void)t1;

    RayTracer::Math::Point3D min(_center.getX() - _radius, _center.getY() - _radius, _center.getZ() - _radius);
    RayTracer::Math::Point3D max(_center.getX() + _radius, _center.getY() + _radius, _center.getZ() + _radius);

    boundingBox = AxisAlignedBoundingBox(min, max);

    return true;
}

void RayTracer::Forms::Sphere::getSphereUV(const Math::Point3D &point, double &u, double &v)
{
    double theta = acos(-point.getY());
    double phi = atan2(-point.getZ(), point.getX()) + pi;

    u = phi / (2 * pi);
    v = theta / pi;
}
