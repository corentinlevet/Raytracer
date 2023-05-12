/*
** EPITECH PROJECT, 2022
** RectangleXZ.hpp
** File description:
** Header file for the RectangleXZ class
*/

#pragma once

#ifndef RECTANGLEXZ_HPP_
    #define RECTANGLEXZ_HPP_

    #include "AForm.hpp"

    namespace RayTracer::Forms {
        class RectangleXZ : public AForm {
            public:
                RectangleXZ(double x0 = 0.0, double z0 = 0.0, double x1 = 0.0, double z1 = 0.0, double k = 0.0);
                ~RectangleXZ() = default;

                /* Getters and Setters */

                void setX0(double x0) {
                    _x0 = x0;
                }

                void setX1(double x1) {
                    _x1 = x1;
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
                    (void)(y0); (void)(y1);

                    setX0(x0);
                    setX1(x1);
                    setZ0(z0);
                    setZ1(z1);
                    setK(k);
                }

                /* Methods */

                bool hits(const RayTracer::Ray &ray, double t_min, double t_max, HitRecord &hitRecord) const override;

                bool boundingBox(double t0, double t1, AxisAlignedBoundingBox &boundingBox) const override;

            private:
                double _x0;
                double _z0;
                double _x1;
                double _z1;
                double _k;
        };
    }

    extern "C"
    {
        FormPtr entryPointForm();
    }

#endif /* !RECTANGLEXZ_HPP_ */
