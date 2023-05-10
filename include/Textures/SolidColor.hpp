/*
** EPITECH PROJECT, 2022
** SolidColor.hpp
** File description:
** Header file for the SolidColor class
*/

#pragma once

#ifndef SOLIDCOLOR_HPP_
    #define SOLIDCOLOR_HPP_

    #include "ATexture.hpp"

    namespace RayTracer::Textures {
        class SolidColor : public ATexture {
            public:
                SolidColor(const RayTracer::Math::Color &color = {0, 0, 0});
                SolidColor(double red, double green, double blue);
                ~SolidColor() = default;

                /* Getters and setters */

                RayTracer::Math::Color getColor() const {
                    return _color;
                }

                void setColor(const RayTracer::Math::Color &color) {
                    _color = color;
                }

                void setTextureOdd(const std::shared_ptr<ITexture> &texture) {
                    (void)texture;
                }

                void setTextureEven(const std::shared_ptr<ITexture> &texture) {
                    (void)texture;
                }

                void setScale(double scale) {
                    (void)scale;
                }

                /* Methods */

                RayTracer::Math::Color value(double u, double v, const RayTracer::Math::Point3D &p) const override;

            private:
                RayTracer::Math::Color _color;
        };
    }

    extern "C"
    {
        TexturePtr entryPointTexture();
    }

#endif /* !SOLIDCOLOR_HPP_ */
