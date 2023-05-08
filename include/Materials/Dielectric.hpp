/*
** EPITECH PROJECT, 2022
** Dielectric.hpp
** File description:
** Header file for the Dielectric class
*/

#pragma once

#ifndef DIELECTRIC_HPP_
    #define DIELECTRIC_HPP_

    #include "AMaterial.hpp"

    namespace RayTracer::Materials {
        class Dielectric : public AMaterial {
            public:
                Dielectric(const RayTracer::Math::Color &albedo = {0, 0, 0});
                ~Dielectric() = default;

                static double reflectance(double cosine, double refractionRatio);

                bool scatter(const RayTracer::Ray &ray, const RayTracer::Forms::HitRecord &record, RayTracer::Math::Color &attenuation, RayTracer::Ray &scattered) const override;
        };
    }

    extern "C"
    {
        MaterialPtr entryPointMaterial();
    }

#endif /* !DIELECTRIC_HPP_ */
