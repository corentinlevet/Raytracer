/*
** EPITECH PROJECT, 2022
** IMaterial.hpp
** File description:
** Header file for the Material Interface class
*/

#pragma once

#ifndef IMATERIAL_HPP_
    #define IMATERIAL_HPP_

    #include <memory>
    #include <string>

    #include "Point3D.hpp"

    #include "TextureFactory.hpp"

    namespace RayTracer {
        class Ray;
        namespace Forms {
            class HitRecord;
        }
    }

    namespace RayTracer::Materials {
        class IMaterial {
            public:
                virtual ~IMaterial() = default;

                /**
                 * @brief Get the Type of the Material
                 *
                 * @return std::string The type of the Material
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
                virtual bool scatter(const RayTracer::Ray &ray, const RayTracer::Forms::HitRecord &record, RayTracer::Math::Color &attenuation, RayTracer::Ray &scattered) const = 0;

                virtual void setAlbedo(const RayTracer::Math::Color &albedo) = 0;

                virtual void setFuzziness(const double fuzz) = 0;

                virtual void setRefractionIndex(const double refractionIndex) = 0;

                virtual void setTexture(const TexturePtr texture) = 0;
        };
    }

    typedef std::shared_ptr<RayTracer::Materials::IMaterial> MaterialPtr;

#endif /* !IMATERIAL_HPP_ */
