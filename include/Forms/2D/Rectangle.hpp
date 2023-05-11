/*
** EPITECH PROJECT, 2022
** Rectangle.hpp
** File description:
** Header file for the Rectangle class
*/

#pragma once

#ifndef RECTANGLE_HPP_
    #define RECTANGLE_HPP_

    #include "AForm.hpp"

    namespace RayTracer::Forms {
        class Rectangle : public AForm {
            public:
                Rectangle(double x0 = 0.0, double y0 = 0.0, double x1 = 0.0, double y1 = 0.0, double k = 0.0);
                ~Rectangle() = default;

                /* Getters and Setters */

                void setX0(double x0) override {
                    _x0 = x0;
                }

                void setX1(double x1) override {
                    _x1 = x1;
                }

                void setY0(double y0) override {
                    _y0 = y0;
                }

                void setY1(double y1) override {
                    _y1 = y1;
                }

                void setK(double k) override {
                    _k = k;
                }

                /* Methods */

                bool hits(const RayTracer::Ray &ray, double t_min, double t_max, HitRecord &hitRecord) const override;

                bool boundingBox(double t0, double t1, AxisAlignedBoundingBox &boundingBox) const override;

            private:
                double _x0;
                double _y0;
                double _x1;
                double _y1;
                double _k;
        };
    }

    extern "C"
    {
        FormPtr entryPointForm();
    }

#endif /* !RECTANGLE_HPP_ */
