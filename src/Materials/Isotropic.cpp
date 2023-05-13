/*
** EPITECH PROJECT, 2022
** Isotropic.cpp
** File description:
** Source file for the Isotropic class
*/

#include "Isotropic.hpp"

#include "HitRecord.hpp"
#include "Ray.hpp"

#include "TextureFactory.hpp"

extern "C"
{
    MaterialPtr entryPointMaterial()
    {
        return std::make_unique<RayTracer::Materials::Isotropic>();
    }
}

/* Constructor */

RayTracer::Materials::Isotropic::Isotropic(const RayTracer::Math::Color &albedo)
{
    initIsotropic(albedo);
}

RayTracer::Materials::Isotropic::Isotropic(const TexturePtr &texture)
{
    initIsotropic(texture);
}

/* Methods */

bool RayTracer::Materials::Isotropic::scatter(const RayTracer::Ray &ray, const RayTracer::Forms::HitRecord &record, RayTracer::Math::Color &attenuation, RayTracer::Ray &scattered) const
{
    scattered = RayTracer::Ray(record.getPoint(), RayTracer::Math::Vector3D::randomInUnitSphere(), ray.getTime());
    attenuation = _albedo->value(record.getU(), record.getV(), record.getPoint());
    return true;
}

void RayTracer::Materials::Isotropic::initIsotropic(const RayTracer::Math::Color &albedo)
{
    auto solidColor = TextureFactory::createTexture("SolidColor");
    solidColor->setColor(albedo);
    _albedo = solidColor;
}

void RayTracer::Materials::Isotropic::initIsotropic(const TexturePtr &texture)
{
    _albedo = texture;
}
