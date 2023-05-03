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

RayTracer::Raytracer::Raytracer(const std::string &sceneFile)
{
    RayTracer::Parser parser(sceneFile);

    try {
        _camera = parser.getCamera();
        _forms = parser.getForms();
    } catch (...) {
        throw RayTracer::Raytracer::hardError("Raytracer", "Error while parsing the scene file");
    }

    for (auto &form : _forms)
        std::cout << form->getType() << std::endl;
}
