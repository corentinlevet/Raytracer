/*
** EPITECH PROJECT, 2022
** Vector3D.hpp
** File description:
** Header file for the Vector3D class
*/

#pragma once

#ifndef VECTOR3D_HPP_
    #define VECTOR3D_HPP_

    #include <cmath>

    namespace RayTracer::Math {
        class Vector3D {
            public:
                /* Public attributes */

                double _x;
                double _y;
                double _z;

                /* Constructors and destructors */

                /**
                 * @brief Constructs a new Vector3D object by giving the x, y and z coordinates
                 *     (Default constructor)
                 * @param x The x coordinate
                 * @param y The y coordinate
                 * @param z The z coordinate
                **/
                Vector3D(double x = 0, double y = 0, double z = 0);

                /**
                 * @brief Constructs a new Vector3D object by giving another Vector3D object
                 *       (Copy constructor)
                 * @param other The other Vector3D object
                **/
                Vector3D(const Vector3D &other);

                /**
                 * @brief Constructs a new Vector3D object by giving another Vector3D object
                 *       (Move constructor)
                 * @param other The other Vector3D object
                **/
                Vector3D(Vector3D &&other);

                /**
                 * @brief Destroys the Vector3D object
                 *
                 * @note This destructor is default
                **/
                ~Vector3D() = default;

                /* Operators */

                Vector3D &operator=(const Vector3D &other);
                Vector3D &operator=(Vector3D &&other);

                Vector3D operator+(const Vector3D &other) const;
                Vector3D operator+=(const Vector3D &other);
                Vector3D operator-(const Vector3D &other) const;
                Vector3D operator-=(const Vector3D &other);
                Vector3D operator*(const Vector3D &other) const;
                Vector3D operator*=(const Vector3D &other);
                Vector3D operator/(const Vector3D &other) const;
                Vector3D operator/=(const Vector3D &other);

                Vector3D operator*(double value) const;
                Vector3D operator*=(double value);
                Vector3D operator/(double value) const;
                Vector3D operator/=(double value);

                /* Methods */

                /**
                 * @brief Calculates the length of the vector
                 * @return The length of the vector
                **/
                double length() const;

                /**
                 * @brief Calculates the dot product between two vectors
                 * @param other The other vector
                 * @return The dot product
                **/
                double dot(const Vector3D &other) const;
        };
    }

#endif /* !VECTOR3D_HPP_ */
