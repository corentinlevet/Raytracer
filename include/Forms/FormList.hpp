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

                FormList(const std::shared_ptr<RayTracer::Forms::IForm>& form);

                /* Methods */

                void clear();
                void add(const std::shared_ptr<RayTracer::Forms::IForm>& form);

                bool hit(const RayTracer::Ray& ray, double t_min, double t_max, Forms::HitRecord& hitRecord) const;

            private:
                std::vector<std::shared_ptr<RayTracer::Forms::IForm>> _forms;
        };
    }

#endif /* !FORMLIST_HPP_ */
