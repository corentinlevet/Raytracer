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

    #include "AxisAlignedBoundingBox.hpp"

    namespace RayTracer::Forms {
        class Cube : public AForm {
            public:
                Cube();
                ~Cube() = default;
        };
    }

    extern "C"
    {
        FormPtr entryPointForm();
    }

#endif /* !CUBE_HPP_ */