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

    #include "AxisAlignedBoundingBox.hpp"

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

                AxisAlignedBoundingBox getBoundingBox() const override {
                    return AxisAlignedBoundingBox();
                }

                FormPtr getLeft() const override {
                    return nullptr;
                }

                FormPtr getRight() const override {
                    return nullptr;
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

                void setBoundingBox(const AxisAlignedBoundingBox &boundingBox) override {
                    (void)boundingBox;
                }

                void setLeft(const FormPtr &left) override {
                    (void)left;
                }

                void setRight(const FormPtr &right) override {
                    (void)right;
                }

                bool hits(const RayTracer::Ray &ray, double t_min, double t_max, HitRecord &hitRecord) const override {
                    (void)ray; (void)t_min; (void)t_max; (void)hitRecord;
                    return false;
                }

                bool boundingBox(double t0, double t1, AxisAlignedBoundingBox &boundingBox) const override {
                    (void)t0; (void)t1; (void)boundingBox;
                    return false;
                }
        };
    }

    extern "C"
    {
        FormPtr entryPointForm();
    }

#endif /* !CUBE_HPP_ */