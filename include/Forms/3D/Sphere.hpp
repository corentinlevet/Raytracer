/*
** EPITECH PROJECT, 2022
** Sphere.hpp
** File description:
** Header file for the Sphere class
*/

#pragma once

#ifndef SPHERE_HPP_
    #define SPHERE_HPP_

    #include "AForm.hpp"

    #include "AxisAlignedBoundingBox.hpp"

    namespace RayTracer::Forms {
        class Sphere : public AForm {
            public:
                Sphere(double radius = 0, const RayTracer::Math::Point3D &center = {0, 0, 0}, const std::shared_ptr<RayTracer::Materials::IMaterial> &material = nullptr);
                ~Sphere() = default;

                /* Getters and setters */

                void setRadius(double radius) override {
                    _radius = radius;
                }

                void setCenter(const RayTracer::Math::Point3D &center) override {
                    _center = center;
                }

                /* Methods */

                bool hits(const RayTracer::Ray &ray, double t_min, double t_max, HitRecord &hitRecord) const override;

                bool boundingBox(double t0, double t1, AxisAlignedBoundingBox &boundingBox) const override;

                static void getSphereUV(const RayTracer::Math::Point3D &point, double &u, double &v);

            private:
                double _radius;

                RayTracer::Math::Point3D _center;
        };
    }

    extern "C"
    {
        FormPtr entryPointForm();
    }

#endif /* !SPHERE_HPP_ */
