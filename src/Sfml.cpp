/*
** EPITECH PROJECT, 2023
** Raypisseur
** File description:
** Sfml
*/

#include "Sfml.hpp"

RayTracer::Sfml::Sfml()
{
}

RayTracer::Sfml::~Sfml()
{
}

void RayTracer::Sfml::initWindow(int width, int height)
{
    _width = width;
    _height = height;
    _window.create(sf::VideoMode(width, height), "Raytracer");
    _window.setFramerateLimit(60);
    _pixels.resize(width * height);
    _texture.create(_width, _height);
    _x = 0;
    _y = 0;
}

int RayTracer::Sfml::getWidth()
{
    return (_width);
}

int RayTracer::Sfml::getHeight()
{
    return (_height);
}

void RayTracer::Sfml::setWidth(int width)
{
    _width = width;
}

void RayTracer::Sfml::setHeight(int height)
{
    _height = height;
}

void RayTracer::Sfml::printPixel(RayTracer::Math::Color pixelColor)
{
    _window.clear();
    _ColorPixels.push_back(pixelColor);
    sf::Color color(pixelColor.getX(), pixelColor.getY(), pixelColor.getZ(), 255);
    _pixels.push_back(sf::Vertex(sf::Vector2f(_x, _y), color));
    if (_x >= _width) {
        _x = 0;
        _y++;
    } else
        _x++;
    _window.draw(&_pixels[0], _pixels.size(), sf::Points);
    this->display();
}

void RayTracer::Sfml::display()
{
    _window.display();
}
