/*
** EPITECH PROJECT, 2022
** Cube.cpp
** File description:
** Source file for the Cube class
*/

#include "Cube.hpp"

extern "C"
{
    std::unique_ptr<Raytracer::Forms::IForm> entryPoint()
    {
        return std::make_unique<Raytracer::Forms::Cube>();
    }
}

/* Constructor */

Raytracer::Forms::Cube::Cube()
{
    _type = "Cube";
}