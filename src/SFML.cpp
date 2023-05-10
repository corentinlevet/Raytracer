/*
** EPITECH PROJECT, 2022
** SFML.cpp
** File description:
** Source file for the SFML class
*/

#include "SFML.hpp"

/* Constructor & Destructor */

RayTracer::SFML::SFML()
{
    _isWindowOpen = true;
}

RayTracer::SFML::~SFML()
{
    if (_isWindowOpen)
        _window.close();
}

/* Public methods */

void RayTracer::SFML::initWindow(int width, int height)
{
    _window.create(sf::VideoMode(width, height), "Raytracer");
    _window.setFramerateLimit(60);
    _pixels.resize(width * height);
}

void RayTracer::SFML::printPixels(std::vector<RayTracer::Math::Color> pixelColors, int width, int y, int samplesPerPixel)
{
    _window.clear(sf::Color::Black);

    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            _window.close();
            _isWindowOpen = false;
        }
    }

    for (int x = 0; x < width; x++) {
        auto r = pixelColors[x].getX();
        auto g = pixelColors[x].getY();
        auto b = pixelColors[x].getZ();

        auto scale = 1.0 / samplesPerPixel;
        r = sqrt(scale * r);
        g = sqrt(scale * g);
        b = sqrt(scale * b);

        sf::Color color(
            static_cast<sf::Uint8>(255.999 * std::clamp(r, 0.0, 0.999)),
            static_cast<sf::Uint8>(255.999 * std::clamp(g, 0.0, 0.999)),
            static_cast<sf::Uint8>(255.999 * std::clamp(b, 0.0, 0.999))
        );

        _pixels.push_back(sf::Vertex(sf::Vector2f(x, y), color));
    }

    _window.draw(&_pixels[0], _pixels.size(), sf::Points);
    _window.display();
}
