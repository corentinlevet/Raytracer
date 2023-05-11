/*
** EPITECH PROJECT, 2022
** ILight.hpp
** File description:
** Header file for the Light Abstract class
*/

#pragma once

#ifndef ILIGHT_HPP_
    #define ILIGHT_HPP_

    #include "IMaterial.hpp"

    namespace RayTracer::Lights {
        class ILight : public RayTracer::Materials::IMaterial {
            public:
                virtual ~ILight() = default;

                /**
                 * @brief Get the Type of the Light
                 *
                 * @return std::string The type of the Light
                **/
                virtual std::string getName() const = 0;

                /**
                 * @brief Scatter the Ray
                 *
                 * @param ray The Ray to scatter
                 * @param record The HitRecord of the Ray
                 * @param attenuation The attenuation of the Ray
                 * @param scattered The scattered Ray
                 * @return true If the Ray has been scattered
                 * @return false If the Ray has not been scattered
                **/
                virtual bool scatter(const RayTracer::Ray &ray, const RayTracer::Forms::HitRecord &record, RayTracer::Math::Color &attenuation, RayTracer::Ray &scattered) const {
                    (void)ray; (void)record; (void)attenuation; (void)scattered;
                    return false;
                }

                virtual RayTracer::Math::Color emitted(double u, double v, const RayTracer::Math::Point3D &point) const = 0;

                virtual void setAlbedo(const RayTracer::Math::Color &albedo) {
                    (void)albedo;
                }

                virtual void setFuzziness(const double fuzz) {
                    (void)fuzz;
                }

                virtual void setRefractionIndex(const double refractionIndex) {
                    (void)refractionIndex;
                }

                virtual void setTexture(const TexturePtr texture) {
                    (void)texture;
                }
        };
    }

    typedef std::shared_ptr<RayTracer::Lights::ILight> LightPtr;

#endif /* !ILIGHT_HPP_ */
