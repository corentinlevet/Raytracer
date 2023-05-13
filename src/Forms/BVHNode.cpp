/*
** EPITECH PROJECT, 2022
** BVHNode.cpp
** File description:
** Source file for the BVHNode class
*/

#include "BVHNode.hpp"

#include "HitRecord.hpp"
#include "Random.hpp"

/* Constructors and destructors */

RayTracer::Forms::BVHNode::BVHNode(const FormList &formList, double time0, double time1) : BVHNode(formList.getForms(), 0, formList.getForms().size(), time0, time1) {}

RayTracer::Forms::BVHNode::BVHNode(const std::vector<FormPtr> &forms, size_t start, size_t end, double time0, double time1)
{
    auto formsCopy = forms;

    int axis = randomInt(0, 2);

    size_t objectSpan = end - start;

    if (objectSpan == 1) {
        _left = _right = formsCopy[start];
    } else if (objectSpan == 2) {
        if (axis == 0 && boxXCompare(formsCopy[start], formsCopy[start + 1])) {
            _left = formsCopy[start];
            _right = formsCopy[start + 1];
        } else if (axis == 1 && boxYCompare(formsCopy[start], formsCopy[start + 1])) {
            _left = formsCopy[start];
            _right = formsCopy[start + 1];
        } else if (axis == 2 && boxZCompare(formsCopy[start], formsCopy[start + 1])) {
            _left = formsCopy[start];
            _right = formsCopy[start + 1];
        } else {
            _left = formsCopy[start + 1];
            _right = formsCopy[start];
        }
    } else {
        if (axis == 0)
            std::sort(formsCopy.begin() + start, formsCopy.begin() + end, boxXCompare);
        else if (axis == 1)
            std::sort(formsCopy.begin() + start, formsCopy.begin() + end, boxYCompare);
        else
            std::sort(formsCopy.begin() + start, formsCopy.begin() + end, boxZCompare);

        auto mid = start + objectSpan / 2;

        _left = std::make_shared<BVHNode>(formsCopy, start, mid, time0, time1);
        _right = std::make_shared<BVHNode>(formsCopy, mid, end, time0, time1);
    }

    AxisAlignedBoundingBox boxLeft, boxRight;

    if (!_left->boundingBox(time0, time1, boxLeft) || !_right->boundingBox(time0, time1, boxRight))
        throw std::runtime_error("No bounding box in BVHNode constructor");

    _boundingBox = surroundingBox(boxLeft, boxRight);
}

/* Public Methods */

bool RayTracer::Forms::BVHNode::hits(const RayTracer::Ray &ray, double t_min, double t_max, HitRecord &hitRecord) const
{
    if (!_boundingBox.hit(ray, t_min, t_max))
        return false;

    bool hitLeft = _left->hits(ray, t_min, t_max, hitRecord);
    bool hitRight = _right->hits(ray, t_min, hitLeft ? hitRecord.getT() : t_max, hitRecord);

    return hitLeft || hitRight;
}

bool RayTracer::Forms::BVHNode::boundingBox(double t0, double t1, AxisAlignedBoundingBox &boundingBox) const
{
    (void)t0; (void)t1;
    boundingBox = _boundingBox;
    return true;
}
