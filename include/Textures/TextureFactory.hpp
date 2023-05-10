/*
** EPITECH PROJECT, 2022
** TextureFactory.hpp
** File description:
** Header file for the TextureFactory class
*/

#pragma once

#ifndef TEXTUREFACTORY_HPP_
    #define TEXTUREFACTORY_HPP_

    #include "DLLoader.hpp"

    #include "SolidColor.hpp"

    #include <map>

    namespace RayTracer::Textures {
        class TextureFactory {
            public:
                /**
                 * @brief Create a texture object
                 *
                 * @param name The name of the texture to create
                 * @return TexturePtr A pointer to the texture material
                **/
                static TexturePtr createTexture(const std::string &name);
        };
    }

    typedef RayTracer::Textures::TextureFactory TextureFactory;

#endif /* !TEXTUREFACTORY_HPP_ */
