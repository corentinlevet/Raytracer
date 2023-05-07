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

    typedef std::shared_ptr<RayTracer::Forms::IForm> FormPtr;

    const double infinity = std::numeric_limits<double>::infinity();
    const double pi = 3.1415926535897932385;

    inline double degreesToRadians(double degrees) {
        return degrees * pi / 180;
    }

    namespace RayTracer::Forms {
        class FormFactory {
            public:
                /**
                 * @brief Create a form object
                 *
                 * @param name The name of the form to create
                 * @return std::unique_ptr<IForm> A pointer to the created form
                **/
                static FormPtr createForm(const std::string &name);
        };
    }

    typedef RayTracer::Forms::FormFactory FormFactory;

#endif /* !FORMFACTORY_HPP_ */
