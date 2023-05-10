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
    std::vector<RayTracer::Math::Vector3D> ranVector(_pointCount);
    for (int i = 0; i < _pointCount; ++i) {
        ranVector[i] = unitVector(RayTracer::Math::Vector3D::random(-1, 1));
        _ranVector.push_back(ranVector[i]);
    }
    _permX = perlinGeneratePerm();
    _permY = perlinGeneratePerm();
    _permZ = perlinGeneratePerm();
}

RayTracer::Textures::Perlin::Perlin()
{
    _name = "Perlin";
    _noise = Noise();
}

/* Public methods */

double RayTracer::Textures::Noise::noise(const RayTracer::Math::Point3D &p) const
{
    auto u = p.getX() - floor(p.getX());
    auto v = p.getY() - floor(p.getY());
    auto w = p.getZ() - floor(p.getZ());
    u = u * u * (3 - 2 * u);
    v = v * v * (3 - 2 * v);
    w = w * w * (3 - 2 * w);

    auto i = static_cast<int>(floor(p.getX()));
    auto j = static_cast<int>(floor(p.getY()));
    auto k = static_cast<int>(floor(p.getZ()));

    std::vector<std::vector<std::vector<RayTracer::Math::Vector3D>>> c(2, std::vector<std::vector<RayTracer::Math::Vector3D>>(2, std::vector<RayTracer::Math::Vector3D>(2)));

    for (int di = 0; di < 2; di++) {
        for (int dj = 0; dj < 2; dj++) {
            for (int dk = 0; dk < 2; dk++) {
                c[di][dj][dk] = _ranVector[_permX[(i + di) & 255] ^ _permY[(j + dj) & 255] ^ _permZ[(k + dk) & 255]];
            }
        }
    }

    return trilinearInterpolation(c, u, v, w);
}

RayTracer::Math::Color RayTracer::Textures::Perlin::value(double u, double v, const RayTracer::Math::Point3D &p) const
{
    (void)u; (void)v;
    return RayTracer::Math::Color(1, 1, 1) * 0.5 * (1.0 + _noise.noise(p * _scale));
}

/* Private methods */

std::vector<int> RayTracer::Textures::Noise::perlinGeneratePerm()
{
    std::vector<int> p(_pointCount);

    for (int i = 0; i < Noise::_pointCount; ++i)
        p[i] = i;

    permute(p, Noise::_pointCount);

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

double RayTracer::Textures::Noise::trilinearInterpolation(std::vector<std::vector<std::vector<RayTracer::Math::Vector3D>>> c, double u, double v, double w)
{
    auto accum = 0.0;
    auto uu = u * u * (3 - 2 * u);
    auto vv = v * v * (3 - 2 * v);
    auto ww = w * w * (3 - 2 * w);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                RayTracer::Math::Vector3D weight(u - i, v - j, w - k);
                accum += (i * uu + (1 - i) * (1 - uu)) *
                        (j * vv + (1 - j) * (1 - vv)) *
                        (k * ww + (1 - k) * (1 - ww)) *
                        dot(c[i][j][k], weight);
            }
        }
    }

    return accum;
}
