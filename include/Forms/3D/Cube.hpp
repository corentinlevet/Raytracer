/*
** EPITECH PROJECT, 2022
** Cube.hpp
** File description:
** Header file for the Cube class
*/

#pragma once

#ifndef CUBE_HPP_
    #define CUBE_HPP_

    #include "AForm.hpp"

    namespace Raytracer::Forms {
        class Cube : public AForm {
            public:
                Cube();
                ~Cube() = default;
        };
    }

    extern "C"
    {
        std::unique_ptr<Raytracer::Forms::IForm> entryPoint();
    }

#endif /* !CUBE_HPP_ */