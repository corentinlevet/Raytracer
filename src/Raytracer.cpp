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
    std::string fileName = _sceneFile.substr(_sceneFile.find_last_of('/') + 1);
    fileName = fileName.substr(0, fileName.find_last_of('.'));
    fileName = "screenshots/" + fileName + ".ppm";

    std::ofstream file(fileName, std::ios::out | std::ios::trunc);

    if (!file.is_open()) {
        std::cerr << "Error: could not open file " << fileName << std::endl;
        exit(84);
    }

    std::tuple resolution = _camera.getResolution();

    const int imageWidth = std::get<0>(resolution);
    const int imageHeight = static_cast<int>(std::get<1>(resolution) / _camera.getAspectRatio());

    _sfml.initWindow(imageWidth, imageHeight);

    const int samplesPerPixel = 25;
    const int maxDepth = 50;

    std::vector<RayTracer::Math::Color> pixelColors(imageWidth);

    file << "P3" << std::endl;
    file << imageWidth << " " << imageHeight << std::endl;
    file << "255" << std::endl;

    for (int y = imageHeight - 1; y >= 0; y--) {
        std::cerr << "\rScanlines remaining: " << y << " " << std::flush;
        for (int x = 0; x < imageWidth; x++) {
            RayTracer::Math::Color pixelColor(0, 0, 0);
            for (int s = 0; s < samplesPerPixel; s++) {
                double u = (x + randomDouble()) / (imageWidth - 1);
                double v = (y + randomDouble()) / (imageHeight - 1);
                RayTracer::Ray ray = _camera.ray(u, v);
                pixelColor += ray.rayColor(ray, _camera.getBackground(), _world, maxDepth);
            }
            pixelColor.writeColor(file, samplesPerPixel);
            pixelColors.push_back(pixelColor);
            if (_sfml.isWindowOpen())
                _sfml.checkEventClose();
        }
        if (_sfml.isWindowOpen())
            _sfml.printPixels(pixelColors, imageWidth, imageHeight - y - 1, samplesPerPixel);
        pixelColors.clear();
    }

    _sfml.waitWindowClose();

    file.close();

    std::cerr << "\nDone." << std::endl;
}

/* Constructor */

RayTracer::Raytracer::Raytracer(const std::string &sceneFile)
{
    try {
        _sceneFile = sceneFile;
        RayTracer::Parser parser(sceneFile);
        _camera = parser.getCamera(_camera);
        _world = parser.getWorld();
    } catch (const RayTracer::Parser::hardError &e) {
        throw RayTracer::Raytracer::hardError("Raytracer", "Error while parsing the scene file: " + std::string(e.what()));
    }
}
