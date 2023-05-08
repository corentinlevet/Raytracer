/*
** EPITECH PROJECT, 2022
** Metal.hpp
** File description:
** Header file for the Metal class
*/

#pragma once

#ifndef METAL_HPP_
    #define METAL_HPP_

    #include "AMaterial.hpp"

    namespace RayTracer::Materials {
        class Metal : public AMaterial {
            public:
                Metal(const RayTracer::Math::Color &albedo = {0, 0, 0});
                ~Metal() = default;

                bool scatter(const RayTracer::Ray &ray, const RayTracer::Forms::HitRecord &record, RayTracer::Math::Color &attenuation, RayTracer::Ray &scattered) const override;
        };
    }

    extern "C"
    {
        MaterialPtr entryPointMaterial();
    }

#endif /* !METAL_HPP_ */
