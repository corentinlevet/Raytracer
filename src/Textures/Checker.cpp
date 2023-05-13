/*
** EPITECH PROJECT, 2022
** Checker.cpp
** File description:
** Source file for the Checker class
*/

#include "Checker.hpp"

#include "TextureFactory.hpp"

extern "C"
{
    TexturePtr entryPointTexture()
    {
        return std::make_unique<RayTracer::Textures::Checker>();
    }
}

/* Constructors */

RayTracer::Textures::Checker::Checker()
{
    _name = "Checker";
}

RayTracer::Textures::Checker::Checker(const TexturePtr &even, const TexturePtr &odd) : _even(even), _odd(odd)
{
    _name = "Checker";
}

RayTracer::Textures::Checker::Checker(const RayTracer::Math::Color color1, const RayTracer::Math::Color color2)
{
    _name = "Checker";
    _even = TextureFactory::createTexture("SolidColor");
    _even->setColor(color1);
    _odd = TextureFactory::createTexture("SolidColor");
    _odd->setColor(color2);
}

/* Public methods */

RayTracer::Math::Color RayTracer::Textures::Checker::value(double u, double v, const RayTracer::Math::Point3D &p) const
{
    auto sines = sin(10 * p.getX()) * sin(10 * p.getY()) * sin(10 * p.getZ());
    if (sines < 0)
        return _odd->value(u, v, p);
    return _even->value(u, v, p);
}
