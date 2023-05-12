/*
** EPITECH PROJECT, 2022
** RectangleYZ.hpp
** File description:
** Header file for the RectangleYZ class
*/

#pragma once

#ifndef RECTANGLEYZ_HPP_
    #define RECTANGLEYZ_HPP_

    #include "AForm.hpp"

    namespace RayTracer::Forms {
        class RectangleYZ : public AForm {
            public:
                RectangleYZ(double y0 = 0.0, double z0 = 0.0, double y1 = 0.0, double z1 = 0.0, double k = 0.0);
                ~RectangleYZ() = default;

                /* Getters and Setters */

                void setY0(double y0) {
                    _y0 = y0;
                }

                void setY1(double y1) {
                    _y1 = y1;
                }

                void setZ0(double z0) {
                    _z0 = z0;
                }

                void setZ1(double z1) {
                    _z1 = z1;
                }

                void setK(double k) {
                    _k = k;
                }

                void initRectangle(double x0, double x1, double y0, double y1, double z0, double z1, double k) {
                    (void)(x0); (void)(x1);

                    setY0(y0);
                    setY1(y1);
                    setZ0(z0);
                    setZ1(z1);
                    setK(k);
                }

                /* Methods */

                bool hits(const RayTracer::Ray &ray, double t_min, double t_max, HitRecord &hitRecord) const override;

                bool boundingBox(double t0, double t1, AxisAlignedBoundingBox &boundingBox) const override;

            private:
                double _y0;
                double _z0;
                double _y1;
                double _z1;
                double _k;
        };
    }

    extern "C"
    {
        FormPtr entryPointForm();
    }

#endif /* !RECTANGLEYZ_HPP_ */
