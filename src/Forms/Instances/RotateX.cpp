/*
** EPITECH PROJECT, 2022
** RotateX.cpp
** File description:
** Source file for the RotateX class
*/

#include "RotateX.hpp"

#include "AxisAlignedBoundingBox.hpp"
#include "HitRecord.hpp"
#include "Ray.hpp"
#include "Utils.hpp"

extern "C"
{
    FormPtr entryPointForm()
    {
        return std::make_unique<RayTracer::Forms::RotateX>();
    }
}

/* Constructor */

RayTracer::Forms::RotateX::RotateX(const FormPtr &form, double angle)
{
    (void)form; (void)angle;
}

/* Public Methods */

void RayTracer::Forms::RotateX::initRotate(const FormPtr &form, double angle)
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

                auto newy = _cosTheta * y - _sinTheta * z;
                auto newz = _sinTheta * y + _cosTheta * z;

                RayTracer::Math::Vector3D tester(x, newy, newz);

                for (int c = 0; c < 3; c++) {
                    min[c] = std::min(min[c], tester[c]);
                    max[c] = std::max(max[c], tester[c]);
                }
            }
        }
    }

    _boundingBox = AxisAlignedBoundingBox(min, max);
}

bool RayTracer::Forms::RotateX::hits(const RayTracer::Ray &ray, double tMin, double tMax, HitRecord &record) const
{
    auto origin = ray.getOrigin();
    auto direction = ray.getDirection();

    origin[1] = _cosTheta * ray.getOrigin()[1] + _sinTheta * ray.getOrigin()[2];
    origin[2] = -_sinTheta * ray.getOrigin()[1] + _cosTheta * ray.getOrigin()[2];

    direction[1] = _cosTheta * ray.getDirection()[1] + _sinTheta * ray.getDirection()[2];
    direction[2] = -_sinTheta * ray.getDirection()[1] + _cosTheta * ray.getDirection()[2];

    Ray rotatedRay(origin, direction, ray.getTime());

    if (!_form->hits(rotatedRay, tMin, tMax, record))
        return false;

    auto point = record.getPoint();
    auto normal = record.getNormal();

    point[1] = _cosTheta * record.getPoint()[1] - _sinTheta * record.getPoint()[2];
    point[2] = _sinTheta * record.getPoint()[1] + _cosTheta * record.getPoint()[2];

    normal[1] = _cosTheta * record.getNormal()[1] - _sinTheta * record.getNormal()[2];
    normal[2] = _sinTheta * record.getNormal()[1] + _cosTheta * record.getNormal()[2];

    record.setPoint(point);
    record.setNormal(normal);

    return true;
}

bool RayTracer::Forms::RotateX::boundingBox(double t0, double t1, AxisAlignedBoundingBox &boundingBox) const
{
    (void)t0; (void)t1;
    boundingBox = _boundingBox;
    return _hasBox;
}
