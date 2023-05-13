/*
** EPITECH PROJECT, 2022
** RotateZ.cpp
** File description:
** Source file for the RotateZ class
*/

#include "RotateZ.hpp"

#include "AxisAlignedBoundingBox.hpp"
#include "HitRecord.hpp"
#include "Ray.hpp"
#include "Utils.hpp"

extern "C"
{
    FormPtr entryPointForm()
    {
        return std::make_unique<RayTracer::Forms::RotateZ>();
    }
}

/* Constructor */

RayTracer::Forms::RotateZ::RotateZ(const FormPtr &form, double angle)
{
    (void)form; (void)angle;
}

/* Public Methods */

void RayTracer::Forms::RotateZ::initRotate(const FormPtr &form, double angle)
{
    _name = form->getName();
    setAngle(angle);
    setForm(form);

    auto radians = degreesToRadians(_angle);

    _cosTheta = std::cos(radians);
    _sinTheta = std::sin(radians);

    _hasBox = _form->boundingBox(0.0, 1.0, _boundingBox);

    RayTracer::Math::Point3D min(infinity, infinity, infinity);
    RayTracer::Math::Point3D max(-infinity, -infinity, -infinity);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++){
            for (int k = 0; k < 2; k++) {
                auto x = i * _boundingBox.getMaximum().getX() + (1 - i) * _boundingBox.getMinimum().getX();
                auto y = j * _boundingBox.getMaximum().getY() + (1 - j) * _boundingBox.getMinimum().getY();
                auto z = k * _boundingBox.getMaximum().getZ() + (1 - k) * _boundingBox.getMinimum().getZ();

                auto newx = _cosTheta * x + _sinTheta * y;
                auto newy = -_sinTheta * x + _cosTheta * y;

                RayTracer::Math::Vector3D tester(newx, newy, z);

                for (int c = 0; c < 3; c++) {
                    min[c] = std::min(min[c], tester[c]);
                    max[c] = std::max(max[c], tester[c]);
                }
            }
        }
    }

    _boundingBox = AxisAlignedBoundingBox(min, max);
}

bool RayTracer::Forms::RotateZ::hits(const RayTracer::Ray &ray, double tMin, double tMax, HitRecord &record) const
{
    auto origin = ray.getOrigin();
    auto direction = ray.getDirection();

    origin[0] = _cosTheta * ray.getOrigin()[0] - _sinTheta * ray.getOrigin()[1];
    origin[1] = _sinTheta * ray.getOrigin()[0] + _cosTheta * ray.getOrigin()[1];

    direction[0] = _cosTheta * ray.getDirection()[0] - _sinTheta * ray.getDirection()[1];
    direction[1] = _sinTheta * ray.getDirection()[0] + _cosTheta * ray.getDirection()[1];

    Ray rotatedRay(origin, direction, ray.getTime());

    if (!_form->hits(rotatedRay, tMin, tMax, record))
        return false;

    auto point = record.getPoint();
    auto normal = record.getNormal();

    point[0] = _cosTheta * record.getPoint()[0] + _sinTheta * record.getPoint()[1];
    point[1] = -_sinTheta * record.getPoint()[0] + _cosTheta * record.getPoint()[1];

    normal[0] = _cosTheta * record.getNormal()[0] + _sinTheta * record.getNormal()[1];
    normal[1] = -_sinTheta * record.getNormal()[0] + _cosTheta * record.getNormal()[1];

    record.setPoint(point);
    record.setNormal(normal);

    return true;
}

bool RayTracer::Forms::RotateZ::boundingBox(double t0, double t1, AxisAlignedBoundingBox &boundingBox) const
{
    (void)t0; (void)t1;
    boundingBox = _boundingBox;
    return _hasBox;
}
