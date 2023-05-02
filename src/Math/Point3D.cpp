/*
** EPITECH PROJECT, 2022
** Point3D.cpp
** File description:
** Source file for the Point3D class
*/

#include "Point3D.hpp"

/* Constructors and destructors */

RayTracer::Math::Point3D::Point3D(double x, double y, double z) : _x(x), _y(y), _z(z) {}

RayTracer::Math::Point3D::Point3D(const RayTracer::Math::Point3D &other) : _x(other._x), _y(other._y), _z(other._z) {}

RayTracer::Math::Point3D::Point3D(RayTracer::Math::Point3D &&other) : _x(other._x), _y(other._y), _z(other._z) {}

/* Operators */

RayTracer::Math::Point3D &RayTracer::Math::Point3D::operator=(const RayTracer::Math::Point3D &other)
{
    _x = other._x;
    _y = other._y;
    _z = other._z;
    return *this;
}

RayTracer::Math::Point3D &RayTracer::Math::Point3D::operator=(RayTracer::Math::Point3D &&other)
{
    _x = other._x;
    _y = other._y;
    _z = other._z;
    return *this;
}

RayTracer::Math::Point3D RayTracer::Math::Point3D::operator+(const RayTracer::Math::Vector3D &other)
{
    return RayTracer::Math::Point3D(_x + other._x, _y + other._y, _z + other._z);
}

RayTracer::Math::Point3D RayTracer::Math::Point3D::operator+=(const RayTracer::Math::Vector3D &other)
{
    _x += other._x;
    _y += other._y;
    _z += other._z;
    return *this;
}

RayTracer::Math::Point3D RayTracer::Math::Point3D::operator-(const RayTracer::Math::Vector3D &other)
{
    return RayTracer::Math::Point3D(_x - other._x, _y - other._y, _z - other._z);
}

RayTracer::Math::Point3D RayTracer::Math::Point3D::operator-=(const RayTracer::Math::Vector3D &other)
{
    _x -= other._x;
    _y -= other._y;
    _z -= other._z;
    return *this;
}
