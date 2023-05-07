/*
** EPITECH PROJECT, 2022
** HitRecord.cpp
** File description:
** Source file for the HitRecord class
*/

#include "HitRecord.hpp"
#include "Ray.hpp"

/* Constructors and destructors */

RayTracer::Forms::HitRecord::HitRecord(double t, const RayTracer::Math::Point3D &point, const RayTracer::Math::Vector3D &normal) : _t(t), _point(point), _normal(normal)
{
    _frontFace = false;
}

/* Public methods */

void RayTracer::Forms::HitRecord::setFaceNormal(const RayTracer::Ray &ray, const RayTracer::Math::Vector3D &outwardNormal)
{
    _frontFace = dot(ray.getDirection(), outwardNormal) < 0;
    _normal = _frontFace ? outwardNormal : -outwardNormal;
}
