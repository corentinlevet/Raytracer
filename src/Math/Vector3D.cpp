/*
** EPITECH PROJECT, 2022
** Vector3D.cpp
** File description:
** Source file for the Vector3D class
*/

#include "Vector3D.hpp"

/* Constructors and destructors */

RayTracer::Math::Vector3D::Vector3D(double x, double y, double z) : _x(x), _y(y), _z(z) {}

RayTracer::Math::Vector3D::Vector3D(const RayTracer::Math::Vector3D &other) : _x(other._x), _y(other._y), _z(other._z) {}

RayTracer::Math::Vector3D::Vector3D(RayTracer::Math::Vector3D &&other) : _x(other._x), _y(other._y), _z(other._z) {}

/* Operators */

RayTracer::Math::Vector3D &RayTracer::Math::Vector3D::operator=(const RayTracer::Math::Vector3D &other)
{
    _x = other._x;
    _y = other._y;
    _z = other._z;
    return *this;
}

RayTracer::Math::Vector3D &RayTracer::Math::Vector3D::operator=(RayTracer::Math::Vector3D &&other)
{
    _x = other._x;
    _y = other._y;
    _z = other._z;
    return *this;
}

RayTracer::Math::Vector3D RayTracer::Math::Vector3D::operator+(const RayTracer::Math::Vector3D &other) const
{
    return RayTracer::Math::Vector3D(_x + other._x, _y + other._y, _z + other._z);
}

RayTracer::Math::Vector3D RayTracer::Math::Vector3D::operator+=(const RayTracer::Math::Vector3D &other)
{
    _x += other._x;
    _y += other._y;
    _z += other._z;
    return *this;
}

RayTracer::Math::Vector3D RayTracer::Math::Vector3D::operator-(const RayTracer::Math::Vector3D &other) const
{
    return RayTracer::Math::Vector3D(_x - other._x, _y - other._y, _z - other._z);
}

RayTracer::Math::Vector3D RayTracer::Math::Vector3D::operator-=(const RayTracer::Math::Vector3D &other)
{
    _x -= other._x;
    _y -= other._y;
    _z -= other._z;
    return *this;
}

RayTracer::Math::Vector3D RayTracer::Math::Vector3D::operator*(const RayTracer::Math::Vector3D &other) const
{
    return RayTracer::Math::Vector3D(_x * other._x, _y * other._y, _z * other._z);
}

RayTracer::Math::Vector3D RayTracer::Math::Vector3D::operator*=(const RayTracer::Math::Vector3D &other)
{
    _x *= other._x;
    _y *= other._y;
    _z *= other._z;
    return *this;
}

RayTracer::Math::Vector3D RayTracer::Math::Vector3D::operator/(const RayTracer::Math::Vector3D &other) const
{
    return RayTracer::Math::Vector3D(_x / other._x, _y / other._y, _z / other._z);
}

RayTracer::Math::Vector3D RayTracer::Math::Vector3D::operator/=(const RayTracer::Math::Vector3D &other)
{
    _x /= other._x;
    _y /= other._y;
    _z /= other._z;
    return *this;
}

RayTracer::Math::Vector3D RayTracer::Math::Vector3D::operator*(double value) const
{
    return RayTracer::Math::Vector3D(_x * value, _y * value, _z * value);
}

RayTracer::Math::Vector3D RayTracer::Math::Vector3D::operator*=(double value)
{
    _x *= value;
    _y *= value;
    _z *= value;
    return *this;
}

RayTracer::Math::Vector3D RayTracer::Math::Vector3D::operator/(double value) const
{
    return RayTracer::Math::Vector3D(_x / value, _y / value, _z / value);
}

RayTracer::Math::Vector3D RayTracer::Math::Vector3D::operator/=(double value)
{
    _x /= value;
    _y /= value;
    _z /= value;
    return *this;
}

/* Public methods */

double RayTracer::Math::Vector3D::length() const
{
    return sqrt(_x * _x + _y * _y + _z * _z);
}

double RayTracer::Math::Vector3D::dot(const RayTracer::Math::Vector3D &other) const
{
    return _x * other._x + _y * other._y + _z * other._z;
}
