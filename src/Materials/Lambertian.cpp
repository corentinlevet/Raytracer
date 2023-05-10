/*
** EPITECH PROJECT, 2022
** Lambertian.cpp
** File description:
** Source file for the Lambertian class
*/

#include "Lambertian.hpp"

#include "HitRecord.hpp"
#include "Ray.hpp"

extern "C"
{
    MaterialPtr entryPointMaterial()
    {
        return std::make_unique<RayTracer::Materials::Lambertian>();
    }
}

/* Constructor */

RayTracer::Materials::Lambertian::Lambertian(const RayTracer::Math::Color &albedo)
{
    _albedo = albedo;
    _fuzz = 0.0;
    _refractionIndex = 0.0;
    _name = "Lambertian";
    _texture = TextureFactory::createTexture("SolidColor");
    _texture->setColor(albedo);
}

RayTracer::Materials::Lambertian::Lambertian(const TexturePtr &texture)
{
    _albedo = {0, 0, 0};
    _fuzz = 0.0;
    _refractionIndex = 0.0;
    _name = "Lambertian";
    _texture = texture;
}

/* Public Methods */

bool RayTracer::Materials::Lambertian::scatter(const RayTracer::Ray &ray, const RayTracer::Forms::HitRecord &record, RayTracer::Math::Color &attenuation, RayTracer::Ray &scattered) const
{
    (void)ray;
    RayTracer::Math::Vector3D scatterDirection = record.getNormal() + RayTracer::Math::Vector3D::randomUnitVector();

    if (scatterDirection.nearZero())
        scatterDirection = record.getNormal();

    scattered = RayTracer::Ray(record.getPoint(), scatterDirection, ray.getTime());
    if (_texture != nullptr)
        attenuation = _texture->value(record.getU(), record.getV(), record.getPoint());
    else
        attenuation = _albedo;

    return true;
}
