/*
** EPITECH PROJECT, 2022
** MaterialFactory.cpp
** File description:
** Source file for the MaterialFactory class
*/

#include "MaterialFactory.hpp"

MaterialPtr RayTracer::Materials::MaterialFactory::createMaterial(const std::string &name)
{
    std::map<std::string, std::string> paths = {
        {"Dielectric", "libs/Materials/Dielectric.so"},
        {"Isotropic", "libs/Materials/Isotropic.so"},
        {"Lambertian", "libs/Materials/Lambertian.so"},
        {"Metal", "libs/Materials/Metal.so"}
    };

    MaterialPtr library = DLLoader::loadLibrary<RayTracer::Materials::IMaterial>(paths.at(name), "Material");

    return library;
}
