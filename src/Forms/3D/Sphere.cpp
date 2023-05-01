/*
** EPITECH PROJECT, 2022
** Sphere.cpp
** File description:
** Source file for the Sphere class
*/

#include "Sphere.hpp"

extern "C"
{
    std::unique_ptr<Raytracer::Forms::IForm> entryPoint()
    {
        return std::make_unique<Raytracer::Forms::Sphere>();
    }
}

/* Constructor */

Raytracer::Forms::Sphere::Sphere()
{
    _type = "Sphere";
}
