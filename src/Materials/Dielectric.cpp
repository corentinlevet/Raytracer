/*
** EPITECH PROJECT, 2022
** Dielectric.cpp
** File description:
** Source file for the Dielectric class
*/

#include "Dielectric.hpp"

#include "HitRecord.hpp"
#include "Ray.hpp"

extern "C"
{
    MaterialPtr entryPointMaterial()
    {
        return std::make_unique<RayTracer::Materials::Dielectric>();
    }
}

/* Constructor */

RayTracer::Materials::Dielectric::Dielectric(const RayTracer::Math::Color &albedo)
{
    _albedo = albedo;
    _fuzz = 0.0;
    _refractionIndex = 0.0;
    _name = "Dielectric";
}

/* Public Methods */

bool RayTracer::Materials::Dielectric::scatter(const RayTracer::Ray &ray, const RayTracer::Forms::HitRecord &record, RayTracer::Math::Color &attenuation, RayTracer::Ray &scattered) const
{
    attenuation = Math::Color(1.0, 1.0, 1.0);
    double refractionRatio = record.isFrontFace() ? (1.0 / _refractionIndex) : _refractionIndex;

    Math::Vector3D unitDirection = unitVector(ray.getDirection());
    Math::Vector3D refracted = Math::Vector3D::refract(unitDirection, record.getNormal(), refractionRatio);

    scattered = RayTracer::Ray(record.getPoint(), refracted);

    return true;
}
