/*
** EPITECH PROJECT, 2022
** AForm.hpp
** File description:
** Header file for the Form Abstract class
*/

#pragma once

#ifndef AFORM_HPP_
    #define AFORM_HPP_

    #include "AxisAlignedBoundingBox.hpp"
    #include "IForm.hpp"

    namespace RayTracer::Forms {
        class AForm : public IForm {
            public:
                virtual ~AForm() = default;

                std::string getName() const override final {
                    return _name;
                }

                RayTracer::Math::Color getColor() const override final {
                    return _color;
                }

                void setColor(const RayTracer::Math::Color &color) override final {
                    _color = color;
                }

                void setMaterial(const MaterialPtr &material) override final {
                    _material = material;
                }

                virtual AxisAlignedBoundingBox getBoundingBox() const {
                    return AxisAlignedBoundingBox();
                }

                virtual FormPtr getLeft() const {
                    return nullptr;
                }

                virtual FormPtr getRight() const {
                    return nullptr;
                }

                virtual void setRadius(double radius) {
                    (void)radius;
                }

                virtual void setCenter(const RayTracer::Math::Point3D &center) {
                    (void)center;
                }

                virtual void setCenter0(const RayTracer::Math::Point3D &center0) {
                    (void)center0;
                }

                virtual void setCenter1(const RayTracer::Math::Point3D &center1) {
                    (void)center1;
                }

                virtual void setTime0(double time0) {
                    (void)time0;
                }

                virtual void setTime1(double time1) {
                    (void)time1;
                }

                virtual void setBoundingBox(const AxisAlignedBoundingBox &boundingBox) {
                    (void)boundingBox;
                }

                virtual void setLeft(const FormPtr &left) {
                    (void)left;
                }

                virtual void setRight(const FormPtr &right) {
                    (void)right;
                }

                virtual void initRectangle(double x0, double x1, double y0, double y1, double z0, double z1, double k) {
                    (void)x0; (void)x1; (void)y0; (void)y1; (void)z0; (void)z1; (void)k;
                }

                virtual bool hits(const RayTracer::Ray &ray, double t_min, double t_max, HitRecord &hitRecord) const {
                    (void)ray; (void)t_min; (void)t_max; (void)hitRecord;
                    return false;
                }

                virtual bool boundingBox(double t0, double t1, AxisAlignedBoundingBox &boundingBox) const {
                    (void)t0; (void)t1; (void)boundingBox;
                    return false;
                }

            protected:
                std::string _name;

                RayTracer::Math::Color _color;

                MaterialPtr _material;
        };
    }

#endif /* !AFORM_HPP_ */
