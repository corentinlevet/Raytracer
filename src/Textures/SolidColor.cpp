/*
** EPITECH PROJECT, 2022
** SolidColor.cpp
** File description:
** Source file for the SolidColor class
*/

#include "SolidColor.hpp"

extern "C"
{
    TexturePtr entryPointTexture()
    {
        return std::make_unique<RayTracer::Textures::SolidColor>();
    }
}

/* Constructors */

RayTracer::Textures::SolidColor::SolidColor(const RayTracer::Math::Color &color) : _color(color)
{
    _name = "SolidColor";
}

RayTracer::Textures::SolidColor::SolidColor(double red, double green, double blue) : SolidColor(RayTracer::Math::Color(red, green, blue)) {}

/* Public methods */

RayTracer::Math::Color RayTracer::Textures::SolidColor::value(double u, double v, const RayTracer::Math::Point3D &p) const
{
    (void)u; (void)v; (void)p;
    return _color;
}
