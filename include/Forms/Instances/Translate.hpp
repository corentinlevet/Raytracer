/*
** EPITECH PROJECT, 2022
** Translate.hpp
** File description:
** Header file for the Translate class
*/

#pragma once

#ifndef TRANSLATE_HPP_
    #define TRANSLATE_HPP_

    #include "AForm.hpp"

    #include "AxisAlignedBoundingBox.hpp"

    namespace RayTracer::Forms {
        class Translate : public AForm {
            public:
                Translate(const FormPtr &form = nullptr, const RayTracer::Math::Vector3D &offset = RayTracer::Math::Vector3D());
                ~Translate() = default;

                /* Getters and setters */

                void setForm(const FormPtr &form) {
                    _form = form;
                }

                void setOffset(const RayTracer::Math::Vector3D &offset) {
                    _offset = offset;
                }

                void initTranslate(const FormPtr &form, const RayTracer::Math::Vector3D &offset) {
                    _name = form->getName();
                    _form = form;
                    _offset = offset;
                }

                /* Methods */

                bool hits(const RayTracer::Ray &ray, double t_min, double t_max, HitRecord &hitRecord) const override;

                bool boundingBox(double t0, double t1, AxisAlignedBoundingBox &boundingBox) const override;

            private:
                FormPtr _form;

                RayTracer::Math::Vector3D _offset;
        };
    }

    extern "C"
    {
        FormPtr entryPointForm();
    }

#endif /* !TRANSLATE_HPP_ */
