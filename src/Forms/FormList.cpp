/*
** EPITECH PROJECT, 2022
** FormList.cpp
** File description:
** Source file for the FormList class
*/

#include "FormList.hpp"

#include "AxisAlignedBoundingBox.hpp"
#include "HitRecord.hpp"
#include "Ray.hpp"

/* Constructors and destructors */

RayTracer::Forms::FormList::FormList(const FormPtr &form)
{
    add(form);
}

/* Public methods */

void RayTracer::Forms::FormList::clear()
{
    _forms.clear();
}

void RayTracer::Forms::FormList::add(const FormPtr &form)
{
    _forms.push_back(std::move(form));
}

bool RayTracer::Forms::FormList::hit(const RayTracer::Ray &ray, double t_min, double t_max, HitRecord &hitRecord) const
{
    HitRecord tempHitRecord;
    bool hitAnything = false;
    double closestSoFar = t_max;

    for (const auto &form : _forms) {
        if (form->hits(ray, t_min, closestSoFar, tempHitRecord)) {
            hitAnything = true;
            closestSoFar = tempHitRecord.getT();
            hitRecord = tempHitRecord;
        }
    }
    return hitAnything;
}

bool RayTracer::Forms::FormList::boundingBox(double t0, double t1, AxisAlignedBoundingBox &boundingBox) const
{
    if (_forms.empty())
        return false;
    AxisAlignedBoundingBox tempBox;
    bool firstBox = true;

    for (const auto &form : _forms) {
        if (!form->boundingBox(t0, t1, tempBox))
            return false;
        boundingBox = firstBox ? tempBox : surroundingBox(boundingBox, tempBox);
        firstBox = false;
    }
    return true;
}
