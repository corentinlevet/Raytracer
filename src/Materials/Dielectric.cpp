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

double RayTracer::Materials::Dielectric::reflectance(double cosine, double refractionRatio)
{
    double r0 = (1.0 - refractionRatio) / (1.0 + refractionRatio);
    r0 = r0 * r0;
    return r0 + (1.0 - r0) * pow((1.0 - cosine), 5.0);
}

bool RayTracer::Materials::Dielectric::scatter(const RayTracer::Ray &ray, const RayTracer::Forms::HitRecord &record, RayTracer::Math::Color &attenuation, RayTracer::Ray &scattered) const
{
    attenuation = Math::Color(1.0, 1.0, 1.0);
    double refractionRatio = record.isFrontFace() ? (1.0 / _refractionIndex) : _refractionIndex;

    Math::Vector3D unitDirection = unitVector(ray.getDirection());

    double cosTheta = fmin(dot(-unitDirection, record.getNormal()), 1.0);
    double sinTheta = sqrt(1.0 - cosTheta * cosTheta);

    bool cannotRefract = refractionRatio * sinTheta > 1.0;
    Math::Vector3D direction;

    if (cannotRefract || reflectance(cosTheta, refractionRatio) > randomDouble())
        direction = Math::Vector3D::reflect(unitDirection, record.getNormal());
    else
        direction = Math::Vector3D::refract(unitDirection, record.getNormal(), refractionRatio);

    scattered = RayTracer::Ray(record.getPoint(), direction);

    return true;
}
