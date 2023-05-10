/*
** EPITECH PROJECT, 2022
** Perlin.hpp
** File description:
** Header file for the Perlin class
*/

#pragma once

#ifndef PERLIN_HPP_
    #define PERLIN_HPP_

    #include "ATexture.hpp"

    namespace RayTracer::Textures {
        class Noise {
            public:
                Noise();
                ~Noise() = default;

                double noise(const RayTracer::Math::Point3D &p) const;

            private:
                static const int pointCount = 256;

                std::vector<double> ranFloat;
                std::vector<int> permX;
                std::vector<int> permY;
                std::vector<int> permZ;

                static std::vector<int> perlinGeneratePerm();

                static void permute(std::vector<int> &p, int n);
        };

        class Perlin : public ATexture {
            public:
                Perlin();
                ~Perlin() = default;

                /* Getters and setters */

                RayTracer::Math::Color getColor() const {
                    return RayTracer::Math::Color();
                }

                RayTracer::Textures::Noise getNoise() const {
                    return _noise;
                }

                void setColor(const RayTracer::Math::Color &color) {
                    (void)color;
                }

                void setTextureOdd(const std::shared_ptr<ITexture> &texture) {
                    (void)texture;
                }

                void setTextureEven(const std::shared_ptr<ITexture> &texture) {
                    (void)texture;
                }

                /* Methods */

                RayTracer::Math::Color value(double u, double v, const RayTracer::Math::Point3D &p) const override;

            private:
                RayTracer::Textures::Noise _noise;
        };
    }

    extern "C"
    {
        TexturePtr entryPointTexture();
    }

#endif /* !PERLIN_HPP_ */
