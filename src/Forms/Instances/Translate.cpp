/*
** EPITECH PROJECT, 2022
** Translate.cpp
** File description:
** Source file for the Translate class
*/

#include "Translate.hpp"

#include "AxisAlignedBoundingBox.hpp"
#include "HitRecord.hpp"
#include "Ray.hpp"

extern "C"
{
    FormPtr entryPointForm()
    {
        return std::make_unique<RayTracer::Forms::Translate>();
    }
}

/* Constructor */

RayTracer::Forms::Translate::Translate(const FormPtr &form, const RayTracer::Math::Vector3D &offset) : _form(form), _offset(offset)
{
    (void)form; (void)offset;
}

/* Public Methods */

bool RayTracer::Forms::Translate::hits(const RayTracer::Ray &ray, double t_min, double t_max, HitRecord &hitRecord) const
{
    RayTracer::Math::Point3D off(_offset.getX(), _offset.getY(), _offset.getZ());
    Ray movedRay(ray.getOrigin() - off, ray.getDirection(), ray.getTime());
    if (!_form->hits(movedRay, t_min, t_max, hitRecord))
        return false;
    hitRecord.setPoint(hitRecord.getPoint() + off);
    hitRecord.setFaceNormal(movedRay, hitRecord.getNormal());
    return true;
}

bool RayTracer::Forms::Translate::boundingBox(double t0, double t1, AxisAlignedBoundingBox &boundingBox) const
{
    if (!_form->boundingBox(t0, t1, boundingBox))
        return false;
    RayTracer::Math::Point3D off(_offset.getX(), _offset.getY(), _offset.getZ());
    boundingBox = AxisAlignedBoundingBox(boundingBox.getMinimum() + off, boundingBox.getMaximum() + off);
    return true;
}
