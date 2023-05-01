/*
** EPITECH PROJECT, 2022
** IForm.hpp
** File description:
** Header file for the Form Interface class
*/

#pragma once

#ifndef IFORM_HPP_
    #define IFORM_HPP_

    #include <memory>
    #include <string>

    namespace Raytracer::Forms {
        class IForm {
            public:
                virtual ~IForm() = default;

                /**
                 * @brief Get the Type of the Form
                 *
                 * @return std::string The type of the Form
                **/
                virtual std::string getType() const = 0;
        };
    }

#endif /* !IFORM_HPP_ */
