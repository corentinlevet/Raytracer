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

                virtual RayTracer::Math::Color getColor() const {
                    return RayTracer::Math::Color();
                }

                virtual void setColor(const RayTracer::Math::Color &color) {
                    (void)color;
                }

                virtual void setTextureOdd(const std::shared_ptr<ITexture> &texture) {
                    (void)texture;
                }

                virtual void setTextureEven(const std::shared_ptr<ITexture> &texture) {
                    (void)texture;
                }

                virtual void setScale(double scale) {
                    (void)scale;
                }

                virtual RayTracer::Math::Color value(double u, double v, const RayTracer::Math::Point3D &p) const = 0;

                virtual void setPath(const std::string &path) {
                    (void)path;
                }

            protected:
                std::string _name;
        };
    }

#endif /* !ATEXTURE_HPP_ */
