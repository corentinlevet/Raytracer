/*
** EPITECH PROJECT, 2022
** Cylinder.cpp
** File description:
** Source file for the Cylinder class
*/

#include "Cylinder.hpp"

#include "AxisAlignedBoundingBox.hpp"
#include "HitRecord.hpp"
#include "Ray.hpp"
#include "Utils.hpp"

extern "C"
{
    FormPtr entryPointForm()
    {
        return std::make_unique<RayTracer::Forms::Cylinder>();
    }
}

/* Constructor */

RayTracer::Forms::Cylinder::Cylinder(double radius, double height, const RayTracer::Math::Point3D &center, const std::shared_ptr<RayTracer::Materials::IMaterial> &material) : _radius(radius), _height(height), _center(center)
{
    _material = material;
    _name = "Cylinder";
}

/* Methods */

bool RayTracer::Forms::Cylinder::hits(const RayTracer::Ray &ray, double t_min, double t_max, HitRecord &hitRecord) const
{
    Math::Vector3D oc(ray.getOrigin().getX() - _center.getX(), ray.getOrigin().getY() - _center.getY(), ray.getOrigin().getZ() - _center.getZ());
    double a = ray.getDirection().getX() * ray.getDirection().getX() + ray.getDirection().getZ() * ray.getDirection().getZ();
    double b = 2 * (oc.getX() * ray.getDirection().getX() + oc.getZ() * ray.getDirection().getZ());
    double c = oc.getX() * oc.getX() + oc.getZ() * oc.getZ() - _radius * _radius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return false;
    double sqrtd = sqrt(discriminant);
    double root = (-b - sqrtd) / (2 * a);
    if (root < t_min || t_max < root) {
        root = (-b + sqrtd) / (2 * a);
        if (root < t_min || t_max < root)
            return false;
    }

    double y = ray.pointAt(root).getY();
    if (y < _center.getY() || y > _center.getY() + _height)
        return false;

    hitRecord.setT(root);
    hitRecord.setPoint(ray.pointAt(hitRecord.getT()));
    Math::Point3D outwardNormal = (hitRecord.getPoint() - _center) / _radius;
    Math::Vector3D outwardNormalVector(outwardNormal.getX(), outwardNormal.getY(), outwardNormal.getZ());
    hitRecord.setFaceNormal(ray, outwardNormalVector);
    hitRecord.setMaterial(_material);
    double u = hitRecord.getU(), v = hitRecord.getV();
    getCylinderUV(outwardNormal, u, v);
    hitRecord.setU(u); hitRecord.setV(v);

    return true;
}

bool RayTracer::Forms::Cylinder::boundingBox(double t0, double t1, AxisAlignedBoundingBox &boundingBox) const
{
    (void)t0; (void)t1;
    boundingBox = AxisAlignedBoundingBox(Math::Point3D(_center.getX() - _radius, _center.getY(), _center.getZ() - _radius), Math::Point3D(_center.getX() + _radius, _center.getY() + _height, _center.getZ() + _radius));
    return true;
}

void RayTracer::Forms::Cylinder::getCylinderUV(const RayTracer::Math::Point3D &point, double &u, double &v)
{
    double phi = atan2(point.getZ(), point.getX());
    u = 1 - (phi + M_PI) / (2 * M_PI);
    v = point.getY();
}
