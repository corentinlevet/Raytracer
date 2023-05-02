/*
** EPITECH PROJECT, 2022
** Ray.hpp
** File description:
** Header file for the Ray class
*/

#pragma once

#ifndef RAY_HPP_
    #define RAY_HPP_

    #include "Point3D.hpp"

    namespace RayTracer {
        class Ray {
            public:
                /* Public attributes */

                Math::Point3D _origin;
                Math::Vector3D _direction;

                /* Constructors and destructors */

                /**
                 * @brief Constructs a new Ray object by giving the origin and the direction
                 *     (Default constructor)
                 * @param origin The origin of the ray
                 * @param direction The direction of the ray
                **/
                Ray(const Math::Point3D &origin = Math::Point3D(), const Math::Vector3D &direction = Math::Vector3D());

                /**
                 * @brief Constructs a new Ray object by giving another Ray object
                 *       (Copy constructor)
                 * @param other The other Ray object
                **/
                Ray(const Ray &other);

                /**
                 * @brief Constructs a new Ray object by giving another Ray object
                 *       (Move constructor)
                 * @param other The other Ray object
                **/
                Ray(Ray &&other);

                /**
                 * @brief Destroys the Ray object
                 *
                 * @note This destructor is default
                **/
                ~Ray() = default;

                /* Operators */

                Ray &operator=(const Ray &other);
                Ray &operator=(Ray &&other);
        };
    }

#endif /* !RAY_HPP_ */
