/*
** EPITECH PROJECT, 2022
** Lambertian.hpp
** File description:
** Header file for the Lambertian class
*/

#pragma once

#ifndef LAMBERTIAN_HPP_
    #define LAMBERTIAN_HPP_

    #include "AMaterial.hpp"

    namespace RayTracer::Materials {
        class Lambertian : public AMaterial {
            public:
                Lambertian(const RayTracer::Math::Color &albedo = {0, 0, 0});
                Lambertian(const TexturePtr &texture);
                ~Lambertian() = default;

                bool scatter(const RayTracer::Ray &ray, const RayTracer::Forms::HitRecord &record, RayTracer::Math::Color &attenuation, RayTracer::Ray &scattered) const override;
        };
    }

    extern "C"
    {
        MaterialPtr entryPointMaterial();
    }

#endif /* !LAMBERTIAN_HPP_ */
