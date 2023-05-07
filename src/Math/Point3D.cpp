/*
** EPITECH PROJECT, 2022
** Point3D.cpp
** File description:
** Source file for the Point3D class
*/

#include "Point3D.hpp"

/* Constructors and destructors */

RayTracer::Math::Point3D::Point3D(double x, double y, double z) : _x(x), _y(y), _z(z) {}

RayTracer::Math::Point3D::Point3D(const RayTracer::Math::Point3D &other) : _x(other.getX()), _y(other.getY()), _z(other.getZ()) {}

RayTracer::Math::Point3D::Point3D(RayTracer::Math::Point3D &&other) : _x(other.getX()), _y(other.getY()), _z(other.getZ()) {}

/* Operators */

RayTracer::Math::Point3D &RayTracer::Math::Point3D::operator=(const RayTracer::Math::Point3D &other)
{
    _x = other.getX();
    _y = other.getY();
    _z = other.getZ();
    return *this;
}

RayTracer::Math::Point3D &RayTracer::Math::Point3D::operator=(RayTracer::Math::Point3D &&other)
{
    _x = other.getX();
    _y = other.getY();
    _z = other.getZ();
    return *this;
}

RayTracer::Math::Point3D RayTracer::Math::Point3D::operator-() const
{
    return Point3D(-_x, -_y, -_z);
}

double RayTracer::Math::Point3D::operator[](int index) const
{
    switch (index) {
        case 0:
            return _x;
        case 1:
            return _y;
        case 2:
            return _z;
        default:
            return 0;
    }
}

double &RayTracer::Math::Point3D::operator[](int index)
{
    switch (index) {
        case 0:
            return _x;
        case 1:
            return _y;
        case 2:
            return _z;
        default:
            return _x;
    }
}

RayTracer::Math::Point3D RayTracer::Math::Point3D::operator+=(const RayTracer::Math::Point3D &other)
{
    _x += other.getX();
    _y += other.getY();
    _z += other.getZ();
    return *this;
}

RayTracer::Math::Point3D RayTracer::Math::Point3D::operator-=(const RayTracer::Math::Point3D &other)
{
    _x -= other.getX();
    _y -= other.getY();
    _z -= other.getZ();
    return *this;
}

RayTracer::Math::Point3D RayTracer::Math::Point3D::operator+=(const RayTracer::Math::Vector3D &other)
{
    _x += other.getX();
    _y += other.getY();
    _z += other.getZ();
    return *this;
}

RayTracer::Math::Point3D RayTracer::Math::Point3D::operator*=(double value)
{
    _x *= value;
    _y *= value;
    _z *= value;
    return *this;
}

RayTracer::Math::Point3D RayTracer::Math::Point3D::operator/=(double value)
{
    _x /= value;
    _y /= value;
    _z /= value;
    return *this;
}

/* Public methods */

double RayTracer::Math::Point3D::length() const
{
    return sqrt(lengthSquared());
}

double RayTracer::Math::Point3D::lengthSquared() const
{
    return _x * _x + _y * _y + _z * _z;
}
