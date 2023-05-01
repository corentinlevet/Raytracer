/*
** EPITECH PROJECT, 2022
** FormFactory.cpp
** File description:
** Source file for the FormFactory class
*/

#include "FormFactory.hpp"

std::unique_ptr<Raytracer::Forms::IForm> Raytracer::Forms::FormFactory::createForm(const std::string &name)
{
    std::map<std::string, std::string> paths = {
        {"Cube", "libs/Forms/3D/Cube.so"},
        {"Sphere", "libs/Forms/3D/Sphere.so"}
    };

    std::unique_ptr<Raytracer::Forms::IForm> library = DLLoader::loadLibrary<Raytracer::Forms::IForm>(paths.at(name));

    return library;
}
