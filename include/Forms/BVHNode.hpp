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

    #include "AxisAlignedBoundingBox.hpp"
    #include "FormList.hpp"

    namespace RayTracer::Forms {
        class BVHNode : public AForm {
            public:
                BVHNode() = default;
                BVHNode(const FormList &formList, double time0, double time1);
                BVHNode(const std::vector<FormPtr> &forms, size_t start, size_t end, double time0, double time1);
                ~BVHNode() = default;

                /* Getters and setters */

                double getRadius() const override {
                    return 0;
                }

                RayTracer::Math::Point3D getCenter() const override {
                    return {0, 0, 0};
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

            private:
                AxisAlignedBoundingBox _boundingBox;

                FormPtr _left;
                FormPtr _right;
        };
    }

    inline bool boxCompare(const FormPtr a, const FormPtr b, int axis) {
        RayTracer::Forms::AxisAlignedBoundingBox boxA;
        RayTracer::Forms::AxisAlignedBoundingBox boxB;

        if (!a->boundingBox(0, 0, boxA) || !b->boundingBox(0, 0, boxB))
            std::cerr << "No bounding box in BVHNode constructor." << std::endl;

        return boxA.getMinimum()[axis] < boxB.getMinimum()[axis];
    }

    bool boxXCompare(const FormPtr a, const FormPtr b) {
        return boxCompare(a, b, 0);
    }

    bool boxYCompare(const FormPtr a, const FormPtr b) {
        return boxCompare(a, b, 1);
    }

    bool boxZCompare(const FormPtr a, const FormPtr b) {
        return boxCompare(a, b, 2);
    }

#endif /* !BVHNODE_HPP_ */
