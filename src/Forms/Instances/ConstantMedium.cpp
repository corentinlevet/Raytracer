/*
** EPITECH PROJECT, 2022
** ConstantMedium.cpp
** File description:
** Source file for the ConstantMedium class
*/

#include "ConstantMedium.hpp"

#include "AxisAlignedBoundingBox.hpp"
#include "HitRecord.hpp"
#include "Ray.hpp"
#include "Utils.hpp"

#include "MaterialFactory.hpp"

extern "C"
{
    FormPtr entryPointForm()
    {
        return std::make_unique<RayTracer::Forms::ConstantMedium>();
    }
}

/* Constructor */

RayTracer::Forms::ConstantMedium::ConstantMedium(const FormPtr &boundary, double density, const RayTracer::Math::Color &color)
{
    initConstantMedium(boundary, density, color);
}

/* Public methods */

bool RayTracer::Forms::ConstantMedium::hits(const RayTracer::Ray &ray, double t_min, double t_max, RayTracer::Forms::HitRecord &hitRecord) const
{
    RayTracer::Forms::HitRecord hitRecord1, hitRecord2;

    if (!_boundary->hits(ray, -infinity, infinity, hitRecord1))
        return false;

    if (!_boundary->hits(ray, hitRecord1.getT() + 0.0001, infinity, hitRecord2))
        return false;

    if (hitRecord1.getT() < t_min)
        hitRecord1.setT(t_min);

    if (hitRecord2.getT() > t_max)
        hitRecord2.setT(t_max);

    if (hitRecord1.getT() >= hitRecord2.getT())
        return false;

    if (hitRecord1.getT() < 0)
        hitRecord1.setT(0);

    const auto rayLength = ray.getDirection().length();
    const auto distanceInsideBoundary = (hitRecord2.getT() - hitRecord1.getT()) * rayLength;
    const auto hitDistance = _density * std::log(randomDouble());

    if (hitDistance > distanceInsideBoundary)
        return false;

    hitRecord.setT(hitRecord1.getT() + hitDistance / rayLength);
    hitRecord.setPoint(ray.pointAt(hitRecord.getT()));

    hitRecord.setNormal({1, 0, 0});
    hitRecord.setFrontFace(true);
    hitRecord.setMaterial(_phaseFunction);

    return true;
}

bool RayTracer::Forms::ConstantMedium::boundingBox(double t0, double t1, AxisAlignedBoundingBox &boundingBox) const
{
    return _boundary->boundingBox(t0, t1, boundingBox);
}

void RayTracer::Forms::ConstantMedium::initConstantMedium(const FormPtr &boundary, double density, const RayTracer::Math::Color &color)
{
    _boundary = boundary;
    _density = (-1.0 / density);
    _phaseFunction = MaterialFactory::createMaterial("Isotropic");
    _phaseFunction->initIsotropic(color);
}
