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
        {"Box", "libs/Forms/3D/Box.so"},
        {"ConstantMedium", "libs/Forms/Instances/ConstantMedium.so"},
        {"Cube", "libs/Forms/3D/Cube.so"},
        {"Cylinder", "libs/Forms/3D/Cylinder.so"},
        {"MovingSphere", "libs/Forms/3D/MovingSphere.so"},
        {"RectangleXY", "libs/Forms/2D/RectangleXY.so"},
        {"RectangleXZ", "libs/Forms/2D/RectangleXZ.so"},
        {"RectangleYZ", "libs/Forms/2D/RectangleYZ.so"},
        {"RotateX", "libs/Forms/Instances/RotateX.so"},
        {"RotateY", "libs/Forms/Instances/RotateY.so"},
        {"RotateZ", "libs/Forms/Instances/RotateZ.so"},
        {"Sphere", "libs/Forms/3D/Sphere.so"},
        {"Translate", "libs/Forms/Instances/Translate.so"}
    };

    FormPtr library = DLLoader::loadLibrary<RayTracer::Forms::IForm>(paths.at(name), "Form");

    return library;
}
