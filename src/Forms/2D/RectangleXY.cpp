/*
** EPITECH PROJECT, 2022
** RectangleXY.cpp
** File description:
** Source file for the RectangleXY class
*/

#include "RectangleXY.hpp"

#include "AxisAlignedBoundingBox.hpp"
#include "HitRecord.hpp"
#include "Ray.hpp"

extern "C"
{
    FormPtr entryPointForm()
    {
        return std::make_unique<RayTracer::Forms::RectangleXY>();
    }
}

/* Constructor */

RayTracer::Forms::RectangleXY::RectangleXY(double x0, double y0, double x1, double y1, double k) : _x0(x0), _y0(y0), _x1(x1), _y1(y1), _k(k)
{
    _name = "RectangleXY";
    _material = nullptr;
}

/* Methods */

bool RayTracer::Forms::RectangleXY::hits(const RayTracer::Ray &ray, double t_min, double t_max, HitRecord &hitRecord) const
{
    double t = (_k - ray.getOrigin().getZ()) / ray.getDirection().getZ();

    if (t < t_min || t > t_max)
        return false;

    double x = ray.getOrigin().getX() + t * ray.getDirection().getX();
    double y = ray.getOrigin().getY() + t * ray.getDirection().getY();

    if (x < _x0 || x > _x1 || y < _y0 || y > _y1)
        return false;

    hitRecord.setU((x - _x0) / (_x1 - _x0));
    hitRecord.setV((y - _y0) / (_y1 - _y0));
    hitRecord.setT(t);
    hitRecord.setFaceNormal(ray, Math::Vector3D(0.0, 0.0, 1.0));
    hitRecord.setMaterial(_material);
    hitRecord.setPoint(ray.pointAt(hitRecord.getT()));

    return true;
}

bool RayTracer::Forms::RectangleXY::boundingBox(double t0, double t1, AxisAlignedBoundingBox &boundingBox) const
{
    (void)t0; (void)t1;

    boundingBox = AxisAlignedBoundingBox(Math::Point3D(_x0, _y0, _k - 0.0001), Math::Point3D(_x1, _y1, _k + 0.0001));

    return true;
}
