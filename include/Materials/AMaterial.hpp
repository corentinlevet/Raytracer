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

                void setAlbedo(const RayTracer::Math::Color &albedo) override final {
                    _albedo = albedo;
                }

                void setFuzziness(const double fuzz) override final {
                    _fuzz = fuzz < 0 ? 0 : fuzz > 1 ? 1 : fuzz;
                }

            protected:
                double _fuzz;

                std::string _name;

                RayTracer::Math::Color _albedo;
        };
    }

#endif /* !AMATERIAL_HPP_ */
