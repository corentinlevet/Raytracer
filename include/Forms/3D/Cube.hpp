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

                /* Methods */

                bool hits(const RayTracer::Ray &ray, double t_min, double t_max, HitRecord &hitRecord) const override {
                    (void)ray; (void)t_min; (void)t_max; (void)hitRecord;
                    return false;
                }

                bool boundingBox(double t0, double t1, AxisAlignedBoundingBox &boundingBox) const override {
                    (void)t0; (void)t1; (void)boundingBox;
                    return false;
                }
        };
    }

    extern "C"
    {
        FormPtr entryPointForm();
    }

#endif /* !CUBE_HPP_ */