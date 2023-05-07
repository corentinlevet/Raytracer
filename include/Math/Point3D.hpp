/*
** EPITECH PROJECT, 2022
** Point3D.hpp
** File description:
** Header file for the Point3D class
*/

#pragma once

#ifndef POINT3D_HPP_
    #define POINT3D_HPP_

    #include "Vector3D.hpp"

    namespace RayTracer::Math {
        class Point3D {
            public:
                /* Constructors and destructors */

                /**
                 * @brief Constructs a new Point3D object by giving the x, y and z coordinates
                 *     (Default constructor)
                 * @param x The x coordinate
                 * @param y The y coordinate
                 * @param z The z coordinate
                **/
                Point3D(double x = 0, double y = 0, double z = 0);

                /**
                 * @brief Constructs a new Point3D object by giving another Point3D object
                 *       (Copy constructor)
                 * @param other The other Point3D object
                **/
                Point3D(const Point3D &other);

                /**
                 * @brief Constructs a new Point3D object by giving another Point3D object
                 *       (Move constructor)
                 * @param other The other Point3D object
                **/
                Point3D(Point3D &&other);

                /**
                 * @brief Destroys the Point3D object
                 *
                 * @note This destructor is default
                **/
                ~Point3D() = default;

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

                Point3D &operator=(const Point3D &other);
                Point3D &operator=(Point3D &&other);

                Point3D operator-() const;
                double operator[](int index) const;
                double &operator[](int index);

                Point3D operator+=(const Point3D &other);
                Point3D operator-=(const Point3D &other);

                Point3D operator*=(double value);
                Point3D operator/=(double value);

                Point3D operator+=(const Vector3D &other);

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

    inline std::ostream &operator<<(std::ostream &out, const RayTracer::Math::Point3D &vector) {
        return out << "(" << vector.getX() << ", " << vector.getY() << ", " << vector.getZ() << ")";
    }

    inline RayTracer::Math::Point3D operator+(const RayTracer::Math::Point3D &left, const RayTracer::Math::Point3D &right) {
        return RayTracer::Math::Point3D(left.getX() + right.getX(), left.getY() + right.getY(), left.getZ() + right.getZ());
    }

    inline RayTracer::Math::Point3D operator-(const RayTracer::Math::Point3D &left, const RayTracer::Math::Point3D &right) {
        return RayTracer::Math::Point3D(left.getX() - right.getX(), left.getY() - right.getY(), left.getZ() - right.getZ());
    }

    inline RayTracer::Math::Point3D operator*(const RayTracer::Math::Point3D &left, double right) {
        return RayTracer::Math::Point3D(left.getX() * right, left.getY() * right, left.getZ() * right);
    }

    inline RayTracer::Math::Point3D operator*(double left, const RayTracer::Math::Point3D &right) {
        return RayTracer::Math::Point3D(left * right.getX(), left * right.getY(), left * right.getZ());
    }

    inline RayTracer::Math::Point3D operator*(const RayTracer::Math::Point3D &left, const RayTracer::Math::Point3D &right) {
        return RayTracer::Math::Point3D(left.getX() * right.getX(), left.getY() * right.getY(), left.getZ() * right.getZ());
    }

    inline RayTracer::Math::Point3D operator/(const RayTracer::Math::Point3D &left, double right) {
        return RayTracer::Math::Point3D(left.getX() / right, left.getY() / right, left.getZ() / right);
    }

    inline double dot(const RayTracer::Math::Point3D &left, const RayTracer::Math::Point3D &right) {
        return left.getX() * right.getX() + left.getY() * right.getY() + left.getZ() * right.getZ();
    }

    inline RayTracer::Math::Point3D cross(const RayTracer::Math::Point3D &left, const RayTracer::Math::Point3D &right) {
        return RayTracer::Math::Point3D(
            left.getY() * right.getZ() - left.getZ() * right.getY(),
            left.getZ() * right.getX() - left.getX() * right.getZ(),
            left.getX() * right.getY() - left.getY() * right.getX()
        );
    }

    inline RayTracer::Math::Point3D unitVector(const RayTracer::Math::Point3D &vector) {
        return vector / vector.length();
    }

#endif /* !POINT3D_HPP_ */
