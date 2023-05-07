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
    #include <iostream>

    #include "Color.hpp"

    namespace RayTracer::Math {
        class Vector3D {
            public:
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

                /* Getters and setters */

                double getX() const {
                    return _x;
                }

                double getY() const {
                    return _y;
                }

                double getZ() const {
                    return _z;
                }

                void setX(double x) {
                    _x = x;
                }

                void setY(double y) {
                    _y = y;
                }

                void setZ(double z) {
                    _z = z;
                }

                /* Operators */

                Vector3D &operator=(const Vector3D &other);
                Vector3D &operator=(Vector3D &&other);

                Vector3D operator-() const;
                double operator[](int index) const;
                double &operator[](int index);

                Vector3D operator+=(const Vector3D &other);
                Vector3D operator-=(const Vector3D &other);

                Vector3D operator*=(double value);
                Vector3D operator/=(double value);

                /* Methods */

                /**
                 * @brief Calculates the length of the vector
                 * @return The length of the vector
                **/
                double length() const;

                /**
                 * @brief Calculates the squared length of the vector
                 * @return The squared length of the vector
                **/
                double lengthSquared() const;

            private:
                double _x;
                double _y;
                double _z;
        };
    }

    inline std::ostream &operator<<(std::ostream &out, const RayTracer::Math::Vector3D &vector) {
        return out << "(" << vector.getX() << ", " << vector.getY() << ", " << vector.getZ() << ")";
    }

    inline RayTracer::Math::Vector3D operator+(const RayTracer::Math::Vector3D &left, const RayTracer::Math::Vector3D &right) {
        return RayTracer::Math::Vector3D(left.getX() + right.getX(), left.getY() + right.getY(), left.getZ() + right.getZ());
    }

    inline RayTracer::Math::Vector3D operator-(const RayTracer::Math::Vector3D &left, const RayTracer::Math::Vector3D &right) {
        return RayTracer::Math::Vector3D(left.getX() - right.getX(), left.getY() - right.getY(), left.getZ() - right.getZ());
    }

    inline RayTracer::Math::Vector3D operator*(const RayTracer::Math::Vector3D &left, double right) {
        return RayTracer::Math::Vector3D(left.getX() * right, left.getY() * right, left.getZ() * right);
    }

    inline RayTracer::Math::Vector3D operator*(double left, const RayTracer::Math::Vector3D &right) {
        return RayTracer::Math::Vector3D(left * right.getX(), left * right.getY(), left * right.getZ());
    }

    inline RayTracer::Math::Vector3D operator*(const RayTracer::Math::Vector3D &left, const RayTracer::Math::Vector3D &right) {
        return RayTracer::Math::Vector3D(left.getX() * right.getX(), left.getY() * right.getY(), left.getZ() * right.getZ());
    }

    inline RayTracer::Math::Vector3D operator/(const RayTracer::Math::Vector3D &left, double right) {
        return RayTracer::Math::Vector3D(left.getX() / right, left.getY() / right, left.getZ() / right);
    }

    inline double dot(const RayTracer::Math::Vector3D &left, const RayTracer::Math::Vector3D &right) {
        return left.getX() * right.getX() + left.getY() * right.getY() + left.getZ() * right.getZ();
    }

    inline RayTracer::Math::Vector3D cross(const RayTracer::Math::Vector3D &left, const RayTracer::Math::Vector3D &right) {
        return RayTracer::Math::Vector3D(
            left.getY() * right.getZ() - left.getZ() * right.getY(),
            left.getZ() * right.getX() - left.getX() * right.getZ(),
            left.getX() * right.getY() - left.getY() * right.getX()
        );
    }

    inline RayTracer::Math::Vector3D unitVector(const RayTracer::Math::Vector3D &vector) {
        return vector / vector.length();
    }

#endif /* !VECTOR3D_HPP_ */
