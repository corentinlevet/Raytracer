/*
** EPITECH PROJECT, 2022
** BVHNode.hpp
** File description:
** Header file for the BVHNode class
*/

#pragma once

#ifndef BVHNODE_HPP_
    #define BVHNODE_HPP_

    #include <algorithm>

    #include "FormList.hpp"

    namespace RayTracer::Forms {
        class BVHNode : public AForm {
            public:
                BVHNode() = default;
                BVHNode(const FormList &formList, double time0, double time1);
                BVHNode(const std::vector<FormPtr> &forms, size_t start, size_t end, double time0, double time1);
                ~BVHNode() = default;

                /* Getters and setters */

                AxisAlignedBoundingBox getBoundingBox() const override {
                    return _boundingBox;
                }

                FormPtr getLeft() const override {
                    return _left;
                }

                FormPtr getRight() const override {
                    return _right;
                }

                void setBoundingBox(const AxisAlignedBoundingBox &boundingBox) override {
                    _boundingBox = boundingBox;
                }

                void setLeft(const FormPtr &left) override {
                    _left = left;
                }

                void setRight(const FormPtr &right) override {
                    _right = right;
                }

                /* Methods */

                bool hits(const RayTracer::Ray &ray, double t_min, double t_max, HitRecord &hitRecord) const override;

                bool boundingBox(double t0, double t1, AxisAlignedBoundingBox &boundingBox) const override;

                static bool boxCompare(const FormPtr a, const FormPtr b, int axis) {
                    RayTracer::Forms::AxisAlignedBoundingBox boxA;
                    RayTracer::Forms::AxisAlignedBoundingBox boxB;

                    if (!a->boundingBox(0, 0, boxA) || !b->boundingBox(0, 0, boxB))
                        std::cerr << "No bounding box in BVHNode constructor." << std::endl;

                    return boxA.getMinimum()[axis] < boxB.getMinimum()[axis];
                }

                static bool boxXCompare(const FormPtr a, const FormPtr b) {
                    return boxCompare(a, b, 0);
                }
                static bool boxYCompare(const FormPtr a, const FormPtr b) {
                    return boxCompare(a, b, 1);
                }
                static bool boxZCompare(const FormPtr a, const FormPtr b) {
                    return boxCompare(a, b, 2);
                }

            private:
                AxisAlignedBoundingBox _boundingBox;

                FormPtr _left;
                FormPtr _right;
        };
    }

#endif /* !BVHNODE_HPP_ */
