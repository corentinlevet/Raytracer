/*
** EPITECH PROJECT, 2022
** RotateY.hpp
** File description:
** Header file for the RotateY class
*/

#pragma once

#ifndef ROTATEY_HPP_
    #define ROTATEY_HPP_

    #include "AForm.hpp"

    #include "AxisAlignedBoundingBox.hpp"

    namespace RayTracer::Forms {
        class RotateY : public AForm {
            public:
                RotateY(const FormPtr &form = nullptr, double angle = 0.0);
                ~RotateY() = default;

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

#endif /* !ROTATEY_HPP_ */
