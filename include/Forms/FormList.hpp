/*
** EPITECH PROJECT, 2022
** FormList.hpp
** File description:
** Header file for the FormList class
*/

#pragma once

#ifndef FORMLIST_HPP_
    #define FORMLIST_HPP_

    #include <memory>
    #include <vector>

    #include "FormFactory.hpp"

    namespace RayTracer::Forms {
        class FormList {
            public:
                FormList() = default;
                ~FormList() = default;

                FormList(const FormPtr &form);

                /* Getters and setters */

                const std::vector<FormPtr> &getForms() const {
                    return _forms;
                }

                void setForms(const std::vector<FormPtr> &forms) {
                    _forms = forms;
                }

                /* Methods */

                void clear();
                void add(const FormPtr &form);

                bool hit(const RayTracer::Ray &ray, double t_min, double t_max, HitRecord &hitRecord) const;

                bool boundingBox(double t0, double t1, AxisAlignedBoundingBox &boundingBox) const;

            private:
                std::vector<FormPtr> _forms;
        };
    }

#endif /* !FORMLIST_HPP_ */
