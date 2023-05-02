/*
** EPITECH PROJECT, 2022
** FormFactory.cpp
** File description:
** Source file for the FormFactory class
*/

#include "FormFactory.hpp"

FormPtr RayTracer::Forms::FormFactory::createForm(const std::string &name)
{
    std::map<std::string, std::string> paths = {
        {"Cube", "libs/Forms/3D/Cube.so"},
        {"Sphere", "libs/Forms/3D/Sphere.so"}
    };

    std::unique_ptr<RayTracer::Forms::IForm> library = DLLoader::loadLibrary<RayTracer::Forms::IForm>(paths.at(name));

    return library;
}
