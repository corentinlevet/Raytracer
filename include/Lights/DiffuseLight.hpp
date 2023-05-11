/*
** EPITECH PROJECT, 2022
** DiffuseLight.hpp
** File description:
** Header file for DiffuseLight class
*/

#pragma once

#ifndef DIFFUSELIGHT_HPP_
    #define DIFFUSELIGHT_HPP_

    #include "ALight.hpp"

    namespace RayTracer::Lights {
        class DiffuseLight : public ALight {
            public:
                DiffuseLight(const RayTracer::Math::Color &color = {0, 0, 0});

                ~DiffuseLight() = default;

                RayTracer::Math::Color emitted(double u, double v, const RayTracer::Math::Point3D &point) const override;
        };
    }

    extern "C"
    {
        LightPtr entryPointLight();
    }

#endif /* !DIFFUSELIGHT_HPP_ */
