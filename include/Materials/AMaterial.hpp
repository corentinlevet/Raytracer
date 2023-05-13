/*
** EPITECH PROJECT, 2022
** AMaterial.hpp
** File description:
** Header file for the Material Abstract class
*/

#pragma once

#ifndef AMATERIAL_HPP_
    #define AMATERIAL_HPP_

    #include "IMaterial.hpp"

    namespace RayTracer::Materials {
        class AMaterial : public IMaterial {
            public:
                virtual ~AMaterial() = default;

                std::string getName() const override final {
                    return _name;
                }

                virtual bool scatter(const RayTracer::Ray &ray, const RayTracer::Forms::HitRecord &record, RayTracer::Math::Color &attenuation, RayTracer::Ray &scattered) const = 0;

                virtual RayTracer::Math::Color emitted(double u, double v, const RayTracer::Math::Point3D &point) const override final {
                    (void)u; (void)v; (void)point;
                    return RayTracer::Math::Color(0, 0, 0);
                }

                void setAlbedo(const RayTracer::Math::Color &albedo) override final {
                    _albedo = albedo;
                }

                void setFuzziness(const double fuzz) override final {
                    _fuzz = fuzz < 0 ? 0 : fuzz > 1 ? 1 : fuzz;
                }

                void setRefractionIndex(const double refractionIndex) override final {
                    _refractionIndex = refractionIndex;
                }

                void setTexture(const TexturePtr texture) override final {
                    _texture = texture;
                }

                virtual void initIsotropic(const RayTracer::Math::Color &albedo) {
                    (void)albedo;
                }

                virtual void initIsotropic(const TexturePtr &texture) {
                    (void)texture;
                }

            protected:
                double _fuzz;
                double _refractionIndex;

                std::string _name;

                RayTracer::Math::Color _albedo;

                TexturePtr _texture;
        };
    }

#endif /* !AMATERIAL_HPP_ */
