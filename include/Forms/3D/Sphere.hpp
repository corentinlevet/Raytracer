/*
** EPITECH PROJECT, 2022
** Sphere.hpp
** File description:
** Header file for the Sphere class
*/

#pragma once

#ifndef SPHERE_HPP_
    #define SPHERE_HPP_

    #include "AForm.hpp"

    namespace Raytracer::Forms {
        class Sphere : public AForm {
            public:
                Sphere();
                ~Sphere() = default;
        };
    }

    extern "C"
    {
        std::unique_ptr<Raytracer::Forms::IForm> entryPoint();
    }

#endif /* !SPHERE_HPP_ */
