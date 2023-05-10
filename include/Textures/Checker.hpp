/*
** EPITECH PROJECT, 2022
** Checker.hpp
** File description:
** Header file for the Checker class
*/

#pragma once

#ifndef CHECKER_HPP_
    #define CHECKER_HPP_

    #include "ATexture.hpp"

    namespace RayTracer::Textures {
        class Checker : public ATexture {
            public:
                Checker() = default;
                Checker(const TexturePtr &even, const TexturePtr &odd);
                Checker(const RayTracer::Math::Color color1, const RayTracer::Math::Color color2);
                ~Checker() = default;

                /* Getters and setters */

                RayTracer::Math::Color getColor() const {
                    return RayTracer::Math::Color();
                }

                void setColor(const RayTracer::Math::Color &color) {
                    (void)color;
                }

                void setTextureOdd(const std::shared_ptr<ITexture> &texture) {
                    _odd = texture;
                }

                void setTextureEven(const std::shared_ptr<ITexture> &texture) {
                    _even = texture;
                }

                void setScale(double scale) {
                    (void)scale;
                }

                /* Methods */

                RayTracer::Math::Color value(double u, double v, const RayTracer::Math::Point3D &p) const override;

            private:
                TexturePtr _even;
                TexturePtr _odd;
        };
    }

    extern "C"
    {
        TexturePtr entryPointTexture();
    }

#endif /* !CHECKER_HPP_ */
