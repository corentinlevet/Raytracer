/*
** EPITECH PROJECT, 2022
** Metal.cpp
** File description:
** Source file for the Metal class
*/

#include "Metal.hpp"

#include "HitRecord.hpp"
#include "Ray.hpp"

extern "C"
{
    MaterialPtr entryPointMaterial()
    {
        return std::make_unique<RayTracer::Materials::Metal>();
    }
}

/* Constructor */

RayTracer::Materials::Metal::Metal(const RayTracer::Math::Color &albedo, const double fuzz)
{
    _albedo = albedo;
    _fuzz = fuzz < 0 ? 0 : fuzz > 1 ? 1 : fuzz;
    _refractionIndex = 0.0;
    _name = "Metal";
}

/* Public Methods */

bool RayTracer::Materials::Metal::scatter(const RayTracer::Ray &ray, const RayTracer::Forms::HitRecord &record, RayTracer::Math::Color &attenuation, RayTracer::Ray &scattered) const
{
    RayTracer::Math::Vector3D reflected = RayTracer::Math::Vector3D::reflect(unitVector(ray.getDirection()), record.getNormal());
    scattered = RayTracer::Ray(record.getPoint(), reflected + _fuzz * RayTracer::Math::Vector3D::randomInUnitSphere(), ray.getTime());
    attenuation = _albedo;

    return (dot(scattered.getDirection(), record.getNormal()) > 0);
}
