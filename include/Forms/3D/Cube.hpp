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

    namespace RayTracer::Forms {
        class Cube : public AForm {
            public:
                Cube();
                ~Cube() = default;

                /* Methods */

                double getRadius() const override {
                    return 0;
                }

                RayTracer::Math::Point3D getCenter() const override {
                    return {0, 0, 0};
                }

                void setRadius(double radius) override {
                    (void)radius;
                }

                void setCenter(const RayTracer::Math::Point3D &center) override {
                    (void)center;
                }

                bool hits(const RayTracer::Ray &ray) const override {
                    (void)ray;
                    return false;
                }
        };
    }

    extern "C"
    {
        std::unique_ptr<RayTracer::Forms::IForm> entryPoint();
    }

#endif /* !CUBE_HPP_ */