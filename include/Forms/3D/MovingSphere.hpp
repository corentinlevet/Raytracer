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

                double getRadius() const;

                RayTracer::Math::Point3D getCenter() const {
                    return 0;
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

                double getTime0() const;
                double getTime1() const;
                RayTracer::Math::Point3D getCenter0() const;
                RayTracer::Math::Point3D getCenter1() const;

                void setRadius(double radius);

                void setCenter(const RayTracer::Math::Point3D &center) override {
                    (void)center;
                }

                void setTime0(double time0);
                void setTime1(double time1);
                void setCenter0(const RayTracer::Math::Point3D &center0);
                void setCenter1(const RayTracer::Math::Point3D &center1);

                void setBoundingBox(const AxisAlignedBoundingBox &boundingBox) override {
                    (void)boundingBox;
                }

                void setLeft(const FormPtr &left) override {
                    (void)left;
                }

                void setRight(const FormPtr &right) override {
                    (void)right;
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
