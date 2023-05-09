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

    namespace RayTracer::Forms {
        class FormList;
    }

    namespace RayTracer {
        class Ray {
            public:
                /* Constructors and destructors */

                /**
                 * @brief Constructs a new Ray object by giving the origin and the direction
                 *     (Default constructor)
                 * @param origin The origin of the ray
                 * @param direction The direction of the ray
                **/
                Ray(const Math::Point3D &origin = Math::Point3D(), const Math::Vector3D &direction = Math::Vector3D(), double time = 0.0);

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

                /* Getters and setters */

                const Math::Point3D &getOrigin() const {
                    return _origin;
                }

                const Math::Vector3D &getDirection() const {
                    return _direction;
                }

                const double &getTime() const {
                    return _time;
                }

                void setOrigin(const Math::Point3D &origin) {
                    _origin = origin;
                }

                void setDirection(const Math::Vector3D &direction) {
                    _direction = direction;
                }

                /* Operators */

                Ray &operator=(const Ray &other);
                Ray &operator=(Ray &&other);

                /* Methods */

                /**
                 * @brief Computes the point at a given distance from the origin
                 *
                 * @param distance The distance from the origin
                 * @return The point at the given distance from the origin
                **/
                Math::Point3D pointAt(double distance) const;

                /**
                 * @brief Computes the color of the ray
                 *
                 * @param world The world
                 * @return The color of the ray
                **/
                Math::Color rayColor(const RayTracer::Ray &ray, const RayTracer::Forms::FormList &world, int depth) const;

            private:
                Math::Point3D _origin;
                Math::Vector3D _direction;

                double _time;
        };
    }

#endif /* !RAY_HPP_ */
