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

    std::tuple resolution = _camera.getResolution();

    const int imageWidth = std::get<0>(resolution);
    const int imageHeight = static_cast<int>(std::get<1>(resolution) / _camera.getAspectRatio());

    _sfml.initWindow(imageWidth, imageHeight);

    const int samplesPerPixel = 1024;
    const int maxDepth = 50;

    const int numThreads = std::thread::hardware_concurrency();
    const int stripHeight = imageHeight / numThreads;
    const int lostPixels = imageHeight % numThreads;
    std::vector<std::thread> threads(numThreads);
    std::mutex windowMutex;
    std::vector<RayTracer::Math::Color> pixelColorsToWrite(imageWidth * imageHeight);

    for (int j = 1; j <= samplesPerPixel; j *= 2) {
        for (int t = 0; t < numThreads; t++) {
            threads[t] = std::thread([&, t]() {
                std::vector<RayTracer::Math::Color> pixelColors(imageWidth);

                int height = 0;
                int newStripHeight = stripHeight;

                if (lostPixels - t > 0) {
                    newStripHeight++;
                    height = newStripHeight * t;
                } else {
                    height = newStripHeight * t + lostPixels;
                }

                for (int y = height; y < height + newStripHeight + 1 && y < imageHeight; y++) {
                    for (int x = 0; x < imageWidth; x++) {
                        RayTracer::Math::Color pixelColor(0, 0, 0);
                        for (int s = 0; s < j; s++) {
                            double u = (x + randomDouble()) / (imageWidth - 1);
                            double v = (y + randomDouble()) / (imageHeight - 1);
                            RayTracer::Ray ray = _camera.ray(u, v);
                            pixelColor += ray.rayColor(ray, _camera.getBackground(), _world, maxDepth);
                        }
                        pixelColors.push_back(pixelColor);
                        pixelColorsToWrite[(imageHeight - y - 1) * imageWidth + x] = pixelColor;
                        windowMutex.lock();
                        if (_sfml.isWindowOpen())
                            _sfml.checkEventClose();
                        windowMutex.unlock();
                    }
                    windowMutex.lock();
                    if (_sfml.isWindowOpen())
                        _sfml.printPixels(pixelColors, imageWidth, imageHeight - y - 1, j);
                    pixelColors.clear();
                    windowMutex.unlock();
                }
            });
        }

        for (auto& t : threads) {
            t.join();
        }

        std::ofstream file(fileName, std::ios::out | std::ios::trunc);

        if (!file.is_open()) {
            std::cerr << "Error: could not open file " << fileName << std::endl;
            exit(84);
        }

        file << "P3" << std::endl;
        file << imageWidth << " " << imageHeight << std::endl;
        file << "255" << std::endl;

        for (auto &pixelColor : pixelColorsToWrite)
            pixelColor.writeColor(file, j);

        file.close();

        pixelColorsToWrite.clear();
        pixelColorsToWrite.resize(imageWidth * imageHeight);

        std::cerr << "Done writing to file with " << j << " samples per pixel." << std::endl;
    }

    std::cerr << "Done." << std::endl;

    _sfml.waitWindowClose();

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
