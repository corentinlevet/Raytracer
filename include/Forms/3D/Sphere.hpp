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

    namespace RayTracer::Forms {
        class Sphere : public AForm {
            public:
                Sphere(double radius = 0, const RayTracer::Math::Point3D &center = {0, 0, 0}, const std::shared_ptr<RayTracer::Materials::IMaterial> &material = nullptr);
                ~Sphere() = default;

                /* Getters and setters */

                double getRadius() const;
                RayTracer::Math::Point3D getCenter() const;

                void setRadius(double radius);
                void setCenter(const RayTracer::Math::Point3D &center);

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

                /* Methods */

                bool hits(const RayTracer::Ray &ray, double t_min, double t_max, HitRecord &hitRecord) const override;

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
