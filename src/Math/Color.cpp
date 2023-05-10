/*
** EPITECH PROJECT, 2022
** Color.cpp
** File description:
** Source file for the Color class
*/

#include "Color.hpp"

/* Constructors and destructors */

RayTracer::Math::Color::Color(double x, double y, double z) : _x(x), _y(y), _z(z) {}

RayTracer::Math::Color::Color(const RayTracer::Math::Color &other) : _x(other.getX()), _y(other.getY()), _z(other.getZ()) {}

RayTracer::Math::Color::Color(RayTracer::Math::Color &&other) : _x(other.getX()), _y(other.getY()), _z(other.getZ()) {}

/* Operators */

RayTracer::Math::Color &RayTracer::Math::Color::operator=(const RayTracer::Math::Color &other)
{
    _x = other.getX();
    _y = other.getY();
    _z = other.getZ();
    return *this;
}

RayTracer::Math::Color &RayTracer::Math::Color::operator=(RayTracer::Math::Color &&other)
{
    _x = other.getX();
    _y = other.getY();
    _z = other.getZ();
    return *this;
}

RayTracer::Math::Color RayTracer::Math::Color::operator-() const
{
    return Color(-_x, -_y, -_z);
}

double RayTracer::Math::Color::operator[](int index) const
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

double &RayTracer::Math::Color::operator[](int index)
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

RayTracer::Math::Color RayTracer::Math::Color::operator+=(const RayTracer::Math::Color &other)
{
    _x += other.getX();
    _y += other.getY();
    _z += other.getZ();
    return *this;
}

RayTracer::Math::Color RayTracer::Math::Color::operator-=(const RayTracer::Math::Color &other)
{
    _x -= other.getX();
    _y -= other.getY();
    _z -= other.getZ();
    return *this;
}

RayTracer::Math::Color RayTracer::Math::Color::operator*=(double value)
{
    _x *= value;
    _y *= value;
    _z *= value;
    return *this;
}

RayTracer::Math::Color RayTracer::Math::Color::operator/=(double value)
{
    _x /= value;
    _y /= value;
    _z /= value;
    return *this;
}

/* Public methods */

double RayTracer::Math::Color::length() const
{
    return sqrt(lengthSquared());
}

double RayTracer::Math::Color::lengthSquared() const
{
    return _x * _x + _y * _y + _z * _z;
}

void RayTracer::Math::Color::writeColor(std::ostream &out, int samplesPerPixel) const
{
        auto r = _x;
        auto g = _y;
        auto b = _z;

        auto scale = 1.0 / samplesPerPixel;
        r = sqrt(scale * r);
        g = sqrt(scale * g);
        b = sqrt(scale * b);

        out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
            << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
            << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}
