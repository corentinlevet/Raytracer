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
        {"MovingSphere", "libs/Forms/3D/MovingSphere.so"},
        {"Sphere", "libs/Forms/3D/Sphere.so"}
    };

    FormPtr library = DLLoader::loadLibrary<RayTracer::Forms::IForm>(paths.at(name), "Form");

    return library;
}
