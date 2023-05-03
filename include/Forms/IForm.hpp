/*
** EPITECH PROJECT, 2022
** IForm.hpp
** File description:
** Header file for the Form Interface class
*/

#pragma once

#ifndef IFORM_HPP_
    #define IFORM_HPP_

    #include <memory>
    #include <string>

    #include "Ray.hpp"

    namespace RayTracer::Forms {
        class IForm {
            public:
                virtual ~IForm() = default;

                /**
                 * @brief Get the Type of the Form
                 *
                 * @return std::string The type of the Form
                **/
                virtual std::string getType() const = 0;

                /**
                 * @brief Get the Color of the Form
                 *
                 * @return std::tuple<short int, short int, short int> The color of the Form
                **/
                virtual std::tuple<short int, short int, short int> getColor() const = 0;

                /**
                 * @brief Set the Color of the Form
                 *
                 * @param color The new color of the Form
                **/
                virtual void setColor(const std::tuple<short int, short int, short int> &color) = 0;

                virtual double getRadius() const = 0;
                virtual RayTracer::Math::Point3D getCenter() const = 0;

                virtual void setRadius(double radius) = 0;
                virtual void setCenter(const RayTracer::Math::Point3D &center) = 0;

                /**
                 * @brief Checks if the Ray hits the Form
                 *
                 * @param ray The Ray to check
                 * @return true If the Ray hits the Form
                 * @return false If the Ray doesn't hit the Form
                **/
                virtual bool hits(const RayTracer::Ray &ray) const = 0;
        };
    }

#endif /* !IFORM_HPP_ */
