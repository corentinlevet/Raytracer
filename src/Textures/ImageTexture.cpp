/*
** EPITECH PROJECT, 2022
** ImageTexture.cpp
** File description:
** Source file for the ImageTexture class
*/

#include "ImageTexture.hpp"

extern "C"
{
    TexturePtr entryPointTexture()
    {
        return std::make_unique<RayTracer::Textures::ImageTexture>();
    }
}

/* Constructors */

RayTracer::Textures::ImageTexture::ImageTexture() : _data(nullptr), _bytesPerScanline(0), _height(0), _width(0)
{
    _name = "ImageTexture";
}

RayTracer::Textures::ImageTexture::ImageTexture(const std::string &path) : ImageTexture()
{
    setPath(path);
}

/* Public methods */

void RayTracer::Textures::ImageTexture::setPath(const std::string &path)
{
    int componentsPerPixel = 3;

    _data = stbi_load(path.c_str(), &_width, &_height, &componentsPerPixel, componentsPerPixel);

    if (!_data) {
        std::cerr << "ERROR: Could not load texture image file '" << path << "'.\n";
        _width = _height = 0;
    }

    _bytesPerScanline = componentsPerPixel * _width;
}

RayTracer::Math::Color RayTracer::Textures::ImageTexture::value(double u, double v, const RayTracer::Math::Point3D &p) const
{
    (void)p;

    if (_data == nullptr)
        return RayTracer::Math::Color(0, 1, 1);

    u = clamp(u, 0.0, 1.0);
    v = 1.0 - clamp(v, 0.0, 1.0);

    auto i = static_cast<int>(u * _width);
    auto j = static_cast<int>(v * _height);

    if (i >= _width)
        i = _width - 1;
    if (j >= _height)
        j = _height - 1;

    const auto colorScale = 1.0 / 255.0;
    auto pixel = _data + j * _bytesPerScanline + i * 3;

    return RayTracer::Math::Color(colorScale * pixel[0], colorScale * pixel[1], colorScale * pixel[2]);
}
