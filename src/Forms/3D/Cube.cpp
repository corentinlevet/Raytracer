/*
** EPITECH PROJECT, 2022
** Cube.cpp
** File description:
** Source file for the Cube class
*/

#include "Cube.hpp"

extern "C"
{
    FormPtr entryPointForm()
    {
        return std::make_unique<RayTracer::Forms::Cube>();
    }
}

/* Constructor */

RayTracer::Forms::Cube::Cube()
{
    _name = "Cube";
}