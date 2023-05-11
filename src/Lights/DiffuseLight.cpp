/*
** EPITECH PROJECT, 2022
** DiffuseLight.cpp
** File description:
** Source file for DiffuseLight class
*/

#include "DiffuseLight.hpp"

#include "TextureFactory.hpp"

extern "C"
{
    LightPtr entryPointLight()
    {
        return std::make_unique<RayTracer::Lights::DiffuseLight>();
    }
}

/* Constructor */

RayTracer::Lights::DiffuseLight::DiffuseLight(const RayTracer::Math::Color &color)
{
    _name = "DiffuseLight";
    _emit = TextureFactory::createTexture("SolidColor");
    _emit->setColor(color);
}

/* Public Methods */

RayTracer::Math::Color RayTracer::Lights::DiffuseLight::emitted(double u, double v, const RayTracer::Math::Point3D &point) const
{
    return _emit->value(u, v, point);
}
