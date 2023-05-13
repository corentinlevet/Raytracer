/*
** EPITECH PROJECT, 2022
** ALight.hpp
** File description:
** Header file for the Light Abstract class
*/

#pragma once

#ifndef ALIGHT_HPP_
    #define ALIGHT_HPP_

    #include "ILight.hpp"

    namespace RayTracer::Lights {
        class ALight : public ILight {
            public:
                virtual ~ALight() = default;

                std::string getName() const override final {
                    return _name;
                }

                void setTexture(const TexturePtr texture) override final {
                    _emit = texture;
                }

                virtual RayTracer::Math::Color emitted(double u, double v, const RayTracer::Math::Point3D &point) const = 0;

                virtual void initIsotropic(const RayTracer::Math::Color &albedo) {
                    (void)albedo;
                }

                virtual void initIsotropic(const TexturePtr &texture) {
                    (void)texture;
                }

            protected:
                std::string _name;

                TexturePtr _emit;
        };
    }

#endif /* !ALIGHT_HPP_ */
