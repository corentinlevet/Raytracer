/*
** EPITECH PROJECT, 2022
** Vector3D.cpp
** File description:
** Source file for the Vector3D class
*/

#include "Vector3D.hpp"

/* Constructors and destructors */

RayTracer::Math::Vector3D::Vector3D(double x, double y, double z) : _x(x), _y(y), _z(z) {}

RayTracer::Math::Vector3D::Vector3D(const RayTracer::Math::Vector3D &other) : _x(other.getX()), _y(other.getY()), _z(other.getZ()) {}

RayTracer::Math::Vector3D::Vector3D(RayTracer::Math::Vector3D &&other) : _x(other.getX()), _y(other.getY()), _z(other.getZ()) {}

/* Operators */

RayTracer::Math::Vector3D &RayTracer::Math::Vector3D::operator=(const RayTracer::Math::Vector3D &other)
{
    _x = other.getX();
    _y = other.getY();
    _z = other.getZ();
    return *this;
}

RayTracer::Math::Vector3D &RayTracer::Math::Vector3D::operator=(RayTracer::Math::Vector3D &&other)
{
    _x = other.getX();
    _y = other.getY();
    _z = other.getZ();
    return *this;
}

RayTracer::Math::Vector3D RayTracer::Math::Vector3D::operator-() const
{
    return Vector3D(-_x, -_y, -_z);
}

double RayTracer::Math::Vector3D::operator[](int index) const
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

double &RayTracer::Math::Vector3D::operator[](int index)
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

RayTracer::Math::Vector3D RayTracer::Math::Vector3D::operator+=(const RayTracer::Math::Vector3D &other)
{
    _x += other.getX();
    _y += other.getY();
    _z += other.getZ();
    return *this;
}

RayTracer::Math::Vector3D RayTracer::Math::Vector3D::operator-=(const RayTracer::Math::Vector3D &other)
{
    _x -= other.getX();
    _y -= other.getY();
    _z -= other.getZ();
    return *this;
}

RayTracer::Math::Vector3D RayTracer::Math::Vector3D::operator*=(double value)
{
    _x *= value;
    _y *= value;
    _z *= value;
    return *this;
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
    return sqrt(lengthSquared());
}

double RayTracer::Math::Vector3D::lengthSquared() const
{
    return _x * _x + _y * _y + _z * _z;
}

RayTracer::Math::Vector3D RayTracer::Math::Vector3D::randomInUnitSphere()
{
    while (true) {
        auto p = Vector3D::random(-1, 1);
        if (p.lengthSquared() >= 1)
            continue;
        return p;
    }
}

RayTracer::Math::Vector3D RayTracer::Math::Vector3D::randomInUnitDisk()
{
    while (true) {
        auto p = Vector3D(randomDouble(-1, 1), randomDouble(-1, 1), 0);
        if (p.lengthSquared() >= 1)
            continue;
        return p;
    }
}

RayTracer::Math::Vector3D RayTracer::Math::Vector3D::randomUnitVector()
{
    return unitVector(randomInUnitSphere());
}

bool RayTracer::Math::Vector3D::nearZero() const
{
    const auto s = 1e-8;
    return (fabs(_x) < s) && (fabs(_y) < s) && (fabs(_z) < s);
}

RayTracer::Math::Vector3D RayTracer::Math::Vector3D::reflect(const RayTracer::Math::Vector3D &vector, const RayTracer::Math::Vector3D &normal)
{
    return vector - 2 * dot(vector, normal) * normal;
}

RayTracer::Math::Vector3D RayTracer::Math::Vector3D::refract(const RayTracer::Math::Vector3D &uv, const RayTracer::Math::Vector3D &normal, double etaiOverEtat)
{
    auto cosTheta = fmin(dot(-uv, normal), 1.0);
    RayTracer::Math::Vector3D rOutPerp = etaiOverEtat * (uv + cosTheta * normal);
    RayTracer::Math::Vector3D rOutParallel = -sqrt(fabs(1.0 - rOutPerp.lengthSquared())) * normal;
    return rOutPerp + rOutParallel;
}
