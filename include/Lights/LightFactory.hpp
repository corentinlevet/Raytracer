/*
** EPITECH PROJECT, 2022
** LightFactory.hpp
** File description:
** Header file for the LightFactory class
*/

#pragma once

#ifndef LIGHTFACTORY_HPP_
    #define LIGHTFACTORY_HPP_

    #include "DLLoader.hpp"

    #include "DiffuseLight.hpp"

    #include <map>

    namespace RayTracer::Lights {
        class LightFactory {
            public:
                /**
                 * @brief Create a light object
                 *
                 * @param name The name of the light to create
                 * @return LightPtr A pointer to the created light
                **/
                static LightPtr createLight(const std::string &name);
        };
    }

    typedef RayTracer::Lights::LightFactory LightFactory;

#endif /* !LIGHTFACTORY_HPP_ */
