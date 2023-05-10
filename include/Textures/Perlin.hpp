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

                double turbulence(const RayTracer::Math::Point3D &p, int depth = 7) const;

            private:
                static const int _pointCount = 256;

                std::vector<int> _permX;
                std::vector<int> _permY;
                std::vector<int> _permZ;

                std::vector<RayTracer::Math::Vector3D> _ranVector;

                static std::vector<int> perlinGeneratePerm();

                static void permute(std::vector<int> &p, int n);

                static double trilinearInterpolation(std::vector<std::vector<std::vector<RayTracer::Math::Vector3D>>> c, double u, double v, double w);
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

                void setScale(double scale) {
                    _scale = scale;
                }

                /* Methods */

                RayTracer::Math::Color value(double u, double v, const RayTracer::Math::Point3D &p) const override;

            private:
                double _scale;

                RayTracer::Textures::Noise _noise;
        };
    }

    extern "C"
    {
        TexturePtr entryPointTexture();
    }

#endif /* !PERLIN_HPP_ */
