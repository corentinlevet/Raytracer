/*
** EPITECH PROJECT, 2022
** RectangleYZ.cpp
** File description:
** Source file for the RectangleYZ class
*/

#include "RectangleYZ.hpp"

#include "AxisAlignedBoundingBox.hpp"
#include "HitRecord.hpp"
#include "Ray.hpp"

extern "C"
{
    FormPtr entryPointForm()
    {
        return std::make_unique<RayTracer::Forms::RectangleYZ>();
    }
}

/* Constructor */

RayTracer::Forms::RectangleYZ::RectangleYZ(double y0, double z0, double y1, double z1, double k) : _y0(y0), _z0(z0), _y1(y1), _z1(z1), _k(k)
{
    _name = "RectangleYZ";
    _material = nullptr;
}

/* Methods */

bool RayTracer::Forms::RectangleYZ::hits(const RayTracer::Ray &ray, double t_min, double t_max, HitRecord &hitRecord) const
{
    double t = (_k - ray.getOrigin().getX()) / ray.getDirection().getX();

    if (t < t_min || t > t_max)
        return false;

    double y = ray.getOrigin().getY() + t * ray.getDirection().getY();
    double z = ray.getOrigin().getZ() + t * ray.getDirection().getZ();

    if (y < _y0 || y > _y1 || z < _z0 || z > _z1)
        return false;

    hitRecord.setU((y - _y0) / (_y1 - _y0));
    hitRecord.setV((z - _z0) / (_z1 - _z0));
    hitRecord.setT(t);
    hitRecord.setFaceNormal(ray, Math::Vector3D(1.0, 0.0, 0.0));
    hitRecord.setMaterial(_material);
    hitRecord.setPoint(ray.pointAt(hitRecord.getT()));

    return true;
}

bool RayTracer::Forms::RectangleYZ::boundingBox(double t0, double t1, AxisAlignedBoundingBox &boundingBox) const
{
    (void)t0; (void)t1;

    boundingBox = AxisAlignedBoundingBox(Math::Point3D(_k - 0.0001, _y0, _z0), Math::Point3D(_k + 0.0001, _y1, _z1));

    return true;
}