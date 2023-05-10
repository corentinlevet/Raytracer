/*
** EPITECH PROJECT, 2022
** ITexture.hpp
** File description:
** Header file for the Texture Interface class
*/

#pragma once

#ifndef ITEXTURE_HPP_
    #define ITEXTURE_HPP_

    #include <memory>
    #include <string>

    #include "Point3D.hpp"

    namespace RayTracer::Textures {
        class ITexture {
            public:
                virtual ~ITexture() = default;

                /**
                 * @brief Get the Type of the Texture
                 *
                 * @return std::string The type of the Texture
                **/
                virtual std::string getName() const = 0;

                virtual RayTracer::Math::Color getColor() const = 0;

                virtual void setColor(const RayTracer::Math::Color &color) = 0;

                virtual void setTextureOdd(const std::shared_ptr<ITexture> &texture) = 0;
                virtual void setTextureEven(const std::shared_ptr<ITexture> &texture) = 0;

                virtual void setScale(double scale) = 0;

                virtual RayTracer::Math::Color value(double u, double v, const RayTracer::Math::Point3D &p) const = 0;

                virtual void setPath(const std::string &path) = 0;
        };
    }

    typedef std::shared_ptr<RayTracer::Textures::ITexture> TexturePtr;

#endif /* !ITEXTURE_HPP_ */
