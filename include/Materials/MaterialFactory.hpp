/*
** EPITECH PROJECT, 2022
** MaterialFactory.hpp
** File description:
** Header file for the MaterialFactory class
*/

#pragma once

#ifndef MATERIALFACTORY_HPP_
    #define MATERIALFACTORY_HPP_

    #include "DLLoader.hpp"

    #include "Lambertian.hpp"
    #include "Metal.hpp"

    #include <map>

    namespace RayTracer::Materials {
        class MaterialFactory {
            public:
                /**
                 * @brief Create a material object
                 *
                 * @param name The name of the material to create
                 * @return MaterialPtr A pointer to the created material
                **/
                static MaterialPtr createMaterial(const std::string &name);
        };
    }

    typedef RayTracer::Materials::MaterialFactory MaterialFactory;

#endif /* !MATERIALFACTORY_HPP_ */
