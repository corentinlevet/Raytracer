/*
** EPITECH PROJECT, 2022
** AxisAlignedBoundingBox.hpp
** File description:
** Header file for the AxisAlignedBoundingBox class
*/

#pragma once

#ifndef AXISALIGNEDBOUNDINGBOX_HPP_
    #define AXISALIGNEDBOUNDINGBOX_HPP_

    #include "Point3D.hpp"

    namespace RayTracer {
        class Ray;
    }

    namespace RayTracer::Forms {
        class AxisAlignedBoundingBox {
            public:
                AxisAlignedBoundingBox() = default;
                AxisAlignedBoundingBox(const RayTracer::Math::Point3D &minimum, const RayTracer::Math::Point3D &maximum);
                ~AxisAlignedBoundingBox() = default;

                /* Getters and setters */

                const RayTracer::Math::Point3D &getMinimum() const {
                    return _minimum;
                }

                const RayTracer::Math::Point3D &getMaximum() const {
                    return _maximum;
                }

                void setMinimum(const RayTracer::Math::Point3D &minimum) {
                    _minimum = minimum;
                }

                void setMaximum(const RayTracer::Math::Point3D &maximum) {
                    _maximum = maximum;
                }

                /* Methods */

                bool hit(const RayTracer::Ray &ray, double t_min, double t_max) const;

            private:
                RayTracer::Math::Point3D _minimum;
                RayTracer::Math::Point3D _maximum;
        };
    }

    inline RayTracer::Forms::AxisAlignedBoundingBox surroundingBox(const RayTracer::Forms::AxisAlignedBoundingBox &box0, const RayTracer::Forms::AxisAlignedBoundingBox &box1) {
        RayTracer::Math::Point3D minimum(
            std::min(box0.getMinimum().getX(), box1.getMinimum().getX()),
            std::min(box0.getMinimum().getY(), box1.getMinimum().getY()),
            std::min(box0.getMinimum().getZ(), box1.getMinimum().getZ())
        );
        RayTracer::Math::Point3D maximum(
            std::max(box0.getMaximum().getX(), box1.getMaximum().getX()),
            std::max(box0.getMaximum().getY(), box1.getMaximum().getY()),
            std::max(box0.getMaximum().getZ(), box1.getMaximum().getZ())
        );

        return RayTracer::Forms::AxisAlignedBoundingBox(minimum, maximum);
    }

#endif /* !AXISALIGNEDBOUNDINGBOX_HPP_ */
