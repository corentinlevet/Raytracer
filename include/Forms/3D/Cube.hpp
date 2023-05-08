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

                void setCenter0(const RayTracer::Math::Point3D &center0) override {
                    (void)center0;
                }

                void setCenter1(const RayTracer::Math::Point3D &center1) override {
                    (void)center1;
                }

                void setTime0(double time0) override {
                    (void)time0;
                }

                void setTime1(double time1) override {
                    (void)time1;
                }

                bool hits(const RayTracer::Ray &ray, double t_min, double t_max, HitRecord &hitRecord) const override {
                    (void)ray; (void)t_min; (void)t_max; (void)hitRecord;
                    return false;
                }
        };
    }

    extern "C"
    {
        FormPtr entryPointForm();
    }

#endif /* !CUBE_HPP_ */