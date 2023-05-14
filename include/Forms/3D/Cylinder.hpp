/*
** EPITECH PROJECT, 2022
** Cylinder.hpp
** File description:
** Header file for the Cylinder class
*/

#pragma once

#ifndef CYLINDER_HPP_
    #define CYLINDER_HPP_

    #include "AForm.hpp"

    #include "AxisAlignedBoundingBox.hpp"

    namespace RayTracer::Forms {
        class Cylinder : public AForm {
            public:
                Cylinder(double radius = 0, double height = 0, const RayTracer::Math::Point3D &center = {0, 0, 0}, const std::shared_ptr<RayTracer::Materials::IMaterial> &material = nullptr);
                ~Cylinder() = default;

                /* Getters and setters */

                void setRadius(double radius) override {
                    _radius = radius;
                }

                void setHeight(double height) {
                    _height = height;
                }

                void setCenter(const RayTracer::Math::Point3D &center) override {
                    _center = center;
                }

                /* Methods */

                bool hits(const RayTracer::Ray &ray, double t_min, double t_max, HitRecord &hitRecord) const override;

                bool boundingBox(double t0, double t1, AxisAlignedBoundingBox &boundingBox) const override;

                static void getCylinderUV(const RayTracer::Math::Point3D &point, double &u, double &v);

            private:
                double _radius;

                double _height;

                RayTracer::Math::Point3D _center;
        };
    }

    extern "C"
    {
        FormPtr entryPointForm();
    }

#endif /* !CYLINDER_HPP_ */
