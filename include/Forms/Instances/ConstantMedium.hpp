/*
** EPITECH PROJECT, 2022
** ConstantMedium.hpp
** File description:
** Header file for the ConstantMedium class
*/

#pragma once

#ifndef CONSTANTMEDIUM_HPP_
    #define CONSTANTMEDIUM_HPP_

    #include "IMaterial.hpp"
    #include "AForm.hpp"

    namespace RayTracer::Forms {
        class ConstantMedium : public AForm {
            public:
                ConstantMedium(const FormPtr &boundary = nullptr, double density = 0.0, const RayTracer::Math::Color &color = RayTracer::Math::Color(0.0, 0.0, 0.0));
                ~ConstantMedium() = default;

                /* Getters and setters */

                AxisAlignedBoundingBox getBoundingBox() const override {
                    return _boundary->getBoundingBox();
                }

                FormPtr getLeft() const override {
                    return _boundary->getLeft();
                }

                FormPtr getRight() const override {
                    return _boundary->getRight();
                }

                void setBoundingBox(const AxisAlignedBoundingBox &boundingBox) override {
                    _boundary->setBoundingBox(boundingBox);
                }

                void setLeft(const FormPtr &left) override {
                    _boundary->setLeft(left);
                }

                void setRight(const FormPtr &right) override {
                    _boundary->setRight(right);
                }

                /* Methods */

                bool hits(const RayTracer::Ray &ray, double t_min, double t_max, HitRecord &hitRecord) const override;

                bool boundingBox(double t0, double t1, AxisAlignedBoundingBox &boundingBox) const override;

                void initConstantMedium(const FormPtr &boundary, double density, const RayTracer::Math::Color &color);

            private:
                FormPtr _boundary;
                double _density;
                MaterialPtr _phaseFunction;
        };
    }

    extern "C"
    {
        FormPtr entryPointForm();
    }

#endif /* !CONSTANTMEDIUM_HPP_ */
