/*
** EPITECH PROJECT, 2022
** AxisAlignedBoundingBox.cpp
** File description:
** Source file for the AxisAlignedBoundingBox class
*/

#include "AxisAlignedBoundingBox.hpp"

#include "Ray.hpp"

/* Constructors and destructors */

RayTracer::Forms::AxisAlignedBoundingBox::AxisAlignedBoundingBox(const RayTracer::Math::Point3D &minimum, const RayTracer::Math::Point3D &maximum) : _minimum(minimum), _maximum(maximum) {}

/* Public methods */

bool RayTracer::Forms::AxisAlignedBoundingBox::hit(const RayTracer::Ray &ray, double t_min, double t_max) const
{
    for (int a = 0; a < 3; a++) {
        auto invD = 1.0f / ray.getDirection()[a];
        auto t0 = (getMinimum()[a] - ray.getOrigin()[a]) * invD;
        auto t1 = (getMaximum()[a] - ray.getOrigin()[a]) * invD;

        if (invD < 0.0f)
            std::swap(t0, t1);
        t_min = t0 > t_min ? t0 : t_min;
        t_max = t1 < t_max ? t1 : t_max;
        if (t_max <= t_min)
            return false;
    }
    return true;
}
