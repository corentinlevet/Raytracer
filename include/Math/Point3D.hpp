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
                /* Public attributes */

                double _x;
                double _y;
                double _z;

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

                /* Operators */

                Point3D &operator=(const Point3D &other);
                Point3D &operator=(Point3D &&other);

                Point3D operator+(const Vector3D &other);
                Point3D operator+=(const Vector3D &other);
                Point3D operator-(const Vector3D &other);
                Point3D operator-=(const Vector3D &other);
        };
    }

#endif /* !POINT3D_HPP_ */
