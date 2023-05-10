/*
** EPITECH PROJECT, 2022
** ATexture.hpp
** File description:
** Header file for the Texture Abstract class
*/

#pragma once

#ifndef ATEXTURE_HPP_
    #define ATEXTURE_HPP_

    #include "ITexture.hpp"

    namespace RayTracer::Textures {
        class ATexture : public ITexture {
            public:
                virtual ~ATexture() = default;

                std::string getName() const override final {
                    return _name;
                }

                virtual RayTracer::Math::Color getColor() const = 0;

                virtual void setColor(const RayTracer::Math::Color &color) = 0;

                virtual void setTextureOdd(const std::shared_ptr<ITexture> &texture) = 0;
                virtual void setTextureEven(const std::shared_ptr<ITexture> &texture) = 0;

                virtual void setScale(double scale) = 0;

                virtual RayTracer::Math::Color value(double u, double v, const RayTracer::Math::Point3D &p) const = 0;

                virtual void setPath(const std::string &path) = 0;

            protected:
                std::string _name;
        };
    }

#endif /* !ATEXTURE_HPP_ */
