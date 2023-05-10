/*
** EPITECH PROJECT, 2022
** Color.hpp
** File description:
** Header file for the Color class
*/

#pragma once

#ifndef COLOR_HPP_
    #define COLOR_HPP_

    #include <cmath>
    #include <iostream>
    #include <vector>

    namespace RayTracer::Math {
        class Color {
            public:
                /* Constructors and destructors */

                /**
                 * @brief Constructs a new Color object by giving the x, y and z coordinates
                 *     (Default constructor)
                 * @param x The x coordinate
                 * @param y The y coordinate
                 * @param z The z coordinate
                **/
                Color(double x = 0, double y = 0, double z = 0);

                /**
                 * @brief Constructs a new Color object by giving another Color object
                 *       (Copy constructor)
                 * @param other The other Color object
                **/
                Color(const Color &other);

                /**
                 * @brief Constructs a new Color object by giving another Color object
                 *       (Move constructor)
                 * @param other The other Color object
                **/
                Color(Color &&other);

                /**
                 * @brief Destroys the Color object
                 *
                 * @note This destructor is default
                **/
                ~Color() = default;

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

                Color &operator=(const Color &other);
                Color &operator=(Color &&other);

                Color operator-() const;
                double operator[](int index) const;
                double &operator[](int index);

                Color operator+=(const Color &other);
                Color operator-=(const Color &other);

                Color operator*=(double value);
                Color operator/=(double value);

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

                /**
                 * @brief Writes the vector in the given output stream
                 * @param out The output stream
                 * @param samplesPerPixel The number of samples per pixel
                 * @return void
                **/
                void writeColor(std::ostream &out, int samplesPerPixel) const;

            private:
                double _x;
                double _y;
                double _z;
        };
    }

    inline std::ostream &operator<<(std::ostream &out, const RayTracer::Math::Color &vector) {
        return out << "(" << vector.getX() << ", " << vector.getY() << ", " << vector.getZ() << ")";
    }

    inline RayTracer::Math::Color operator+(const RayTracer::Math::Color &left, const RayTracer::Math::Color &right) {
        return RayTracer::Math::Color(left.getX() + right.getX(), left.getY() + right.getY(), left.getZ() + right.getZ());
    }

    inline RayTracer::Math::Color operator-(const RayTracer::Math::Color &left, const RayTracer::Math::Color &right) {
        return RayTracer::Math::Color(left.getX() - right.getX(), left.getY() - right.getY(), left.getZ() - right.getZ());
    }

    inline RayTracer::Math::Color operator*(const RayTracer::Math::Color &left, double right) {
        return RayTracer::Math::Color(left.getX() * right, left.getY() * right, left.getZ() * right);
    }

    inline RayTracer::Math::Color operator*(double left, const RayTracer::Math::Color &right) {
        return RayTracer::Math::Color(left * right.getX(), left * right.getY(), left * right.getZ());
    }

    inline RayTracer::Math::Color operator*(const RayTracer::Math::Color &left, const RayTracer::Math::Color &right) {
        return RayTracer::Math::Color(left.getX() * right.getX(), left.getY() * right.getY(), left.getZ() * right.getZ());
    }

    inline RayTracer::Math::Color operator/(const RayTracer::Math::Color &left, double right) {
        return RayTracer::Math::Color(left.getX() / right, left.getY() / right, left.getZ() / right);
    }

    inline double dot(const RayTracer::Math::Color &left, const RayTracer::Math::Color &right) {
        return left.getX() * right.getX() + left.getY() * right.getY() + left.getZ() * right.getZ();
    }

    inline RayTracer::Math::Color cross(const RayTracer::Math::Color &left, const RayTracer::Math::Color &right) {
        return RayTracer::Math::Color(
            left.getY() * right.getZ() - left.getZ() * right.getY(),
            left.getZ() * right.getX() - left.getX() * right.getZ(),
            left.getX() * right.getY() - left.getY() * right.getX()
        );
    }

    inline RayTracer::Math::Color unitVector(const RayTracer::Math::Color &vector) {
        return vector / vector.length();
    }

    inline double clamp(double value, double min, double max) {
        if (value < min)
            return min;
        if (value > max)
            return max;
        return value;
    }

#endif /* !COLOR_HPP_ */
