/*
** EPITECH PROJECT, 2022
** Raytracer.cpp
** File description:
** Source file for the Raytracer class
*/

#include "Raytracer.hpp"

/* Public methods */

void RayTracer::Raytracer::run()
{

}

/* Constructor */

RayTracer::Raytracer::Raytracer(const std::string &sceneFile) : _sceneFile(sceneFile)
{
    std::ifstream file(sceneFile);
    std::string line;

    if (!file.is_open())
        throw RayTracer::Raytracer::hardError("Raytracer", "Could not open file " + sceneFile);
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
}
