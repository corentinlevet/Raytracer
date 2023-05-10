/*
** EPITECH PROJECT, 2022
** Perlin.cpp
** File description:
** Source file for the Perlin class
*/

#include "Perlin.hpp"

extern "C"
{
    TexturePtr entryPointTexture()
    {
        return std::make_unique<RayTracer::Textures::Perlin>();
    }
}

/* Constructors */

RayTracer::Textures::Noise::Noise()
{
    ranFloat = std::vector<double>(pointCount);
    for (int i = 0; i < pointCount; ++i)
        ranFloat[i] = randomDouble();
    permX = perlinGeneratePerm();
    permY = perlinGeneratePerm();
    permZ = perlinGeneratePerm();
}

RayTracer::Textures::Perlin::Perlin()
{
    _name = "Perlin";
    _noise = Noise();
}

/* Public methods */

double RayTracer::Textures::Noise::noise(const RayTracer::Math::Point3D &p) const
{
    auto i = static_cast<int>(4 * p.getX()) & 255;
    auto j = static_cast<int>(4 * p.getY()) & 255;
    auto k = static_cast<int>(4 * p.getZ()) & 255;

    return ranFloat[permX[i] ^ permY[j] ^ permZ[k]];
}

RayTracer::Math::Color RayTracer::Textures::Perlin::value(double u, double v, const RayTracer::Math::Point3D &p) const
{
    (void)u; (void)v;
    return RayTracer::Math::Color(1, 1, 1) * getNoise().noise(p);
}

/* Private methods */

std::vector<int> RayTracer::Textures::Noise::perlinGeneratePerm()
{
    std::vector<int> p(pointCount);

    for (int i = 0; i < Noise::pointCount; ++i)
        p[i] = i;

    permute(p, Noise::pointCount);

    return p;
}

void RayTracer::Textures::Noise::permute(std::vector<int> &p, int n)
{
    for (int i = n - 1; i > 0; i--) {
        int target = randomInt(0, i);
        int tmp = p[i];
        p[i] = p[target];
        p[target] = tmp;
    }
}
