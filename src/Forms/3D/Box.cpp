/*
** EPITECH PROJECT, 2022
** Box.cpp
** File description:
** Source file for the Box class
*/

#include "Box.hpp"

#include "FormFactory.hpp"

extern "C"
{
    FormPtr entryPointForm()
    {
        return std::make_unique<RayTracer::Forms::Box>();
    }
}

/* Constructor */

RayTracer::Forms::Box::Box(const RayTracer::Math::Point3D &p0, const RayTracer::Math::Point3D &p1, const MaterialPtr &material)
{
    initBox(p0, p1, material);
    _name = "Box";
}

/* Methods */

void RayTracer::Forms::Box::initBox(const RayTracer::Math::Point3D &p0, const RayTracer::Math::Point3D &p1, const MaterialPtr &material)
{
    _p0 = p0;
    _p1 = p1;

    auto rectangleXY1 = FormFactory::createForm("RectangleXY");
    rectangleXY1->initRectangle(p0.getX(), p1.getX(), p0.getY(), p1.getY(), 0, 0, p0.getZ());
    rectangleXY1->setMaterial(material);
    _sides.add(std::move(rectangleXY1));

    auto rectangleXY2 = FormFactory::createForm("RectangleXY");
    rectangleXY2->initRectangle(p0.getX(), p1.getX(), p0.getY(), p1.getY(), 0, 0, p1.getZ());
    rectangleXY2->setMaterial(material);
    _sides.add(std::move(rectangleXY2));

    auto rectangleXZ1 = FormFactory::createForm("RectangleXZ");
    rectangleXZ1->initRectangle(p0.getX(), p1.getX(), 0, 0, p0.getZ(), p1.getZ(), p0.getY());
    rectangleXZ1->setMaterial(material);
    _sides.add(std::move(rectangleXZ1));

    auto rectangleXZ2 = FormFactory::createForm("RectangleXZ");
    rectangleXZ2->initRectangle(p0.getX(), p1.getX(), 0, 0, p0.getZ(), p1.getZ(), p1.getY());
    rectangleXZ2->setMaterial(material);
    _sides.add(std::move(rectangleXZ2));

    auto rectangleYZ1 = FormFactory::createForm("RectangleYZ");
    rectangleYZ1->initRectangle(0, 0, p0.getY(), p1.getY(), p0.getZ(), p1.getZ(), p0.getX());
    rectangleYZ1->setMaterial(material);
    _sides.add(std::move(rectangleYZ1));

    auto rectangleYZ2 = FormFactory::createForm("RectangleYZ");
    rectangleYZ2->initRectangle(0, 0, p0.getY(), p1.getY(), p0.getZ(), p1.getZ(), p1.getX());
    rectangleYZ2->setMaterial(material);
    _sides.add(std::move(rectangleYZ2));
}

bool RayTracer::Forms::Box::hits(const RayTracer::Ray &ray, double t_min, double t_max, HitRecord &hitRecord) const
{
    return _sides.hit(ray, t_min, t_max, hitRecord);
}

bool RayTracer::Forms::Box::boundingBox(double time0, double time1, AxisAlignedBoundingBox &boundingBox) const
{
    (void)time0; (void)time1;
    boundingBox = AxisAlignedBoundingBox(_p0, _p1);
    return true;
}
