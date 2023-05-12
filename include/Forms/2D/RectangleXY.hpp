/*
** EPITECH PROJECT, 2022
** RectangleXY.hpp
** File description:
** Header file for the RectangleXY class
*/

#pragma once

#ifndef RECTANGLEXY_HPP_
    #define RECTANGLEXY_HPP_

    #include "AForm.hpp"

    namespace RayTracer::Forms {
        class RectangleXY : public AForm {
            public:
                RectangleXY(double x0 = 0.0, double y0 = 0.0, double x1 = 0.0, double y1 = 0.0, double k = 0.0);
                ~RectangleXY() = default;

                /* Getters and Setters */

                void setX0(double x0) {
                    _x0 = x0;
                }

                void setX1(double x1) {
                    _x1 = x1;
                }

                void setY0(double y0) {
                    _y0 = y0;
                }

                void setY1(double y1) {
                    _y1 = y1;
                }

                void setK(double k) {
                    _k = k;
                }

                void initRectangle(double x0, double x1, double y0, double y1, double z0, double z1, double k) {
                    (void)(z0); (void)(z1);

                    setX0(x0);
                    setX1(x1);
                    setY0(y0);
                    setY1(y1);
                    setK(k);
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

#endif /* !RECTANGLEXY_HPP_ */
