/*
** EPITECH PROJECT, 2022
** Isotropic.hpp
** File description:
** Header file for the Isotropic class
*/

#pragma once

#ifndef ISOTROPIC_HPP_
    #define ISOTROPIC_HPP_

    #include "AMaterial.hpp"

    namespace RayTracer::Materials {
        class Isotropic : public AMaterial {
            public:
                Isotropic(const RayTracer::Math::Color &albedo = {0, 0, 0});
                Isotropic(const TexturePtr &texture);
                ~Isotropic() = default;

                bool scatter(const RayTracer::Ray &ray, const RayTracer::Forms::HitRecord &record, RayTracer::Math::Color &attenuation, RayTracer::Ray &scattered) const override;

                void initIsotropic(const RayTracer::Math::Color &albedo) override;
                void initIsotropic(const TexturePtr &texture) override;

            private:
                TexturePtr _albedo;
        };
    }

    extern "C"
    {
        MaterialPtr entryPointMaterial();
    }

#endif /* !ISOTROPIC_HPP_ */
