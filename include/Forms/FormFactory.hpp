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

    #include <functional>
    #include <map>

    namespace RayTracer::Forms {
        class FormFactory {
            public:
                /**
                 * @brief Create a form object
                 *
                 * @param name The name of the form to create
                 * @return FormPtr A pointer to the created form
                **/
                static FormPtr createForm(const std::string &name);
        };
    }

    typedef RayTracer::Forms::FormFactory FormFactory;

#endif /* !FORMFACTORY_HPP_ */
