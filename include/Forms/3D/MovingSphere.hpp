/*
** EPITECH PROJECT, 2022
** MovingSphere.hpp
** File description:
** Header file for the MovingSphere class
*/

#pragma once

#ifndef MOVINGSPHERE_HPP_
    #define MOVINGSPHERE_HPP_

    #include "AForm.hpp"

    #include "AxisAlignedBoundingBox.hpp"

    namespace RayTracer::Forms {
        class MovingSphere : public AForm {
            public:
                MovingSphere(
                    const double radius = 0.0,
                    const double time0 = 0.0,
                    const double time1 = 0.0,
                    const RayTracer::Math::Point3D &center0 = {0, 0, 0},
                    const RayTracer::Math::Point3D &center1 = {0, 0, 0},
                    const std::shared_ptr<RayTracer::Materials::IMaterial> &material = nullptr);
                ~MovingSphere() = default;

                /* Getters and setters */

                void setRadius(double radius) override {
                    _radius = radius;
                }

                void setTime0(double time0) override {
                    _time0 = time0;
                }

                void setTime1(double time1) override {
                    _time1 = time1;
                }

                void setCenter0(const RayTracer::Math::Point3D &center0) override {
                    _center0 = center0;
                }

                void setCenter1(const RayTracer::Math::Point3D &center1) override {
                    _center1 = center1;
                }

                /* Methods */

                bool hits(const RayTracer::Ray &ray, double t_min, double t_max, HitRecord &hitRecord) const override;

                bool boundingBox(double t0, double t1, AxisAlignedBoundingBox &boundingBox) const override;

                RayTracer::Math::Point3D center(double time) const;

            private:
                double _radius;

                double _time0;
                double _time1;

                RayTracer::Math::Point3D _center0;
                RayTracer::Math::Point3D _center1;
        };
    }

    extern "C"
    {
        FormPtr entryPointForm();
    }

#endif /* !MOVINGSPHERE_HPP_ */
