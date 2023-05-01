/*
** EPITECH PROJECT, 2022
** AForm.hpp
** File description:
** Header file for the Form Abstract class
*/

#pragma once

#ifndef AFORM_HPP_
    #define AFORM_HPP_

    #include "IForm.hpp"

    namespace Raytracer::Forms {
        class AForm : public IForm {
            public:
                virtual ~AForm() = default;

                std::string getType() const override final {
                    return _type;
                }

            protected:
                std::string _type;
        };
    }

#endif /* !AFORM_HPP_ */
