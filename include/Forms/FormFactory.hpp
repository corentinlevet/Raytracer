/*
** EPITECH PROJECT, 2022
** FormFactory.hpp
** File description:
** Header file for the FormFactory class
*/

#pragma once

#ifndef FORMFACTORY_HPP_
    #define FORMFACTORY_HPP_

    #include "DLLoader.hpp"

    #include "3D/Cube.hpp"
    #include "3D/Sphere.hpp"

    #include <map>

    namespace Raytracer::Forms {
        class FormFactory {
            public:
                /**
                 * @brief Create a form object
                 *
                 * @param name The name of the form to create
                 * @return std::unique_ptr<IForm> A pointer to the created form
                **/
                static std::unique_ptr<IForm> createForm(const std::string &name);
        };
    }

#endif /* !FORMFACTORY_HPP_ */