/*
** EPITECH PROJECT, 2022
** LightFactory.cpp
** File description:
** Source file for the LightFactory class
*/

#include "LightFactory.hpp"

LightPtr RayTracer::Lights::LightFactory::createLight(const std::string &name)
{
    std::map<std::string, std::string> paths = {
        {"Diffuse", "libs/Lights/DiffuseLight.so"}
    };

    LightPtr library = DLLoader::loadLibrary<RayTracer::Lights::ILight>(paths.at(name), "Light");

    return library;
}
