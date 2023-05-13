/*
** EPITECH PROJECT, 2022
** RotateZ.hpp
** File description:
** Header file for the RotateZ class
*/

#pragma once

#ifndef ROTATEZ_HPP_
    #define ROTATEZ_HPP_

    #include "AForm.hpp"

    #include "AxisAlignedBoundingBox.hpp"

    namespace RayTracer::Forms {
        class RotateZ : public AForm {
            public:
                RotateZ(const FormPtr &form = nullptr, double angle = 0.0);
                ~RotateZ() = default;

                /* Getters and setters */

                void setAngle(double angle) {
                    _angle = angle;
                }

                void setForm(const FormPtr &form) {
                    _form = form;
                }

                /* Methods */

                void initRotate(const FormPtr &form, double angle) override;

                bool hits(const RayTracer::Ray &ray, double t_min, double t_max, HitRecord &hitRecord) const override;

                bool boundingBox(double t0, double t1, AxisAlignedBoundingBox &boundingBox) const override;

            private:
                bool _hasBox;

                double _angle;

                double _cosTheta;
                double _sinTheta;

                AxisAlignedBoundingBox _boundingBox;

                FormPtr _form;
        };
    }

    extern "C"
    {
        FormPtr entryPointForm();
    }

#endif /* !ROTATEZ_HPP_ */
