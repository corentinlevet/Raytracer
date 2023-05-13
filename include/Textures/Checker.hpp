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
                Checker();
                Checker(const TexturePtr &even, const TexturePtr &odd);
                Checker(const RayTracer::Math::Color color1, const RayTracer::Math::Color color2);
                ~Checker() = default;

                /* Getters and setters */

                void setTextureOdd(const std::shared_ptr<ITexture> &texture) override {
                    _odd = texture;
                }

                void setTextureEven(const std::shared_ptr<ITexture> &texture) override {
                    _even = texture;
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
