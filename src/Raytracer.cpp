/*
** EPITECH PROJECT, 2022
** Raytracer.cpp
** File description:
** Source file for the Raytracer class
*/

#include "Raytracer.hpp"

#include "Parser.hpp"
#include "Ray.hpp"

/* Public methods */

void RayTracer::Raytracer::run()
{
    std::cout << "P3" << std::endl;
    std::tuple resolution = _camera.getResolution();

    const int imageWidth = std::get<0>(resolution);
    const int imageHeight = static_cast<int>(std::get<1>(resolution) / _camera.getAspectRatio());

    std::cout << imageWidth << " " << imageHeight << std::endl;
    std::cout << "255" << std::endl;

    for (int y = imageHeight - 1; y >= 0; y--) {
        std::cerr << "\rScanlines remaining: " << y << std::flush;
        for (int x = 0; x < imageWidth; x++) {
            double u = double(x) / (imageWidth - 1);
            double v = double(y) / (imageHeight - 1);
            _camera.ray(u, v).rayColor(_world).writeColor(std::cout);
        }
    }

    std::cerr << "\nDone." << std::endl;
}

/* Constructor */

RayTracer::Raytracer::Raytracer(const std::string &sceneFile)
{
    RayTracer::Parser parser(sceneFile);

    try {
        _camera = parser.getCamera(_camera);
        _world = parser.getWorld();
    } catch (...) {
        throw RayTracer::Raytracer::hardError("Raytracer", "Error while parsing the scene file");
    }
}
