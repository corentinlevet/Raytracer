/*
** EPITECH PROJECT, 2022
** RectangleXZ.cpp
** File description:
** Source file for the RectangleXZ class
*/

#include "RectangleXZ.hpp"

#include "AxisAlignedBoundingBox.hpp"
#include "HitRecord.hpp"
#include "Ray.hpp"

extern "C"
{
    FormPtr entryPointForm()
    {
        return std::make_unique<RayTracer::Forms::RectangleXZ>();
    }
}

/* Constructor */

RayTracer::Forms::RectangleXZ::RectangleXZ(double x0, double z0, double x1, double z1, double k) : _x0(x0), _z0(z0), _x1(x1), _z1(z1), _k(k)
{
    _name = "RectangleXZ";
    _material = nullptr;
}

/* Methods */

bool RayTracer::Forms::RectangleXZ::hits(const RayTracer::Ray &ray, double t_min, double t_max, HitRecord &hitRecord) const
{
    double t = (_k - ray.getOrigin().getY()) / ray.getDirection().getY();

    if (t < t_min || t > t_max)
        return false;

    double x = ray.getOrigin().getX() + t * ray.getDirection().getX();
    double z = ray.getOrigin().getZ() + t * ray.getDirection().getZ();

    if (x < _x0 || x > _x1 || z < _z0 || z > _z1)
        return false;

    hitRecord.setU((x - _x0) / (_x1 - _x0));
    hitRecord.setV((z - _z0) / (_z1 - _z0));
    hitRecord.setT(t);
    hitRecord.setFaceNormal(ray, Math::Vector3D(0.0, 1.0, 0.0));
    hitRecord.setMaterial(_material);
    hitRecord.setPoint(ray.pointAt(hitRecord.getT()));

    return true;
}

bool RayTracer::Forms::RectangleXZ::boundingBox(double t0, double t1, AxisAlignedBoundingBox &boundingBox) const
{
    (void)t0; (void)t1;

    boundingBox = AxisAlignedBoundingBox(Math::Point3D(_x0, _k - 0.0001, _z0), Math::Point3D(_x1, _k + 0.0001, _z1));

    return true;
}
