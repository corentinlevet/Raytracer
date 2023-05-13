/*
** EPITECH PROJECT, 2022
** Camera.cpp
** File description:
** Source file for the Camera class
*/

#include "Camera.hpp"

#include "Ray.hpp"

#include <iostream>

/* Constructors and destructors */

RayTracer::Camera::Camera::Camera(const double aperture, const double aspectRatio, const double fov, const double time0, const double time1, std::tuple<int, int> resolution, std::tuple<int, int, int> rotation, const RayTracer::Math::Color &background, const RayTracer::Math::Point3D &origin, const RayTracer::Camera::Screen &screen, const RayTracer::Math::Vector3D u, const RayTracer::Math::Vector3D v, const RayTracer::Math::Vector3D w) : _aspectRatio(aspectRatio), _fov(fov), _time0(time0), _time1(time1), _resolution(resolution), _rotation(rotation), _background(background), _origin(origin), _screen(screen), _u(u), _v(v), _w(w)
{
    _lensRadius = aperture / 2.0;
    _focalLength = 1.0;
    _viewportHeight = 2.0;
    _viewportWidth = _aspectRatio * _viewportHeight;
}

/* Getters and setters */

double RayTracer::Camera::Camera::getAspectRatio() const
{
    return _aspectRatio;
}

double RayTracer::Camera::Camera::getFocalLength() const
{
    return _focalLength;
}

double RayTracer::Camera::Camera::getFov() const
{
    return _fov;
}

double RayTracer::Camera::Camera::getViewportHeight() const
{
    return _viewportHeight;
}

double RayTracer::Camera::Camera::getViewportWidth() const
{
    return _viewportWidth;
}

const std::tuple<int, int> &RayTracer::Camera::Camera::getResolution() const
{
    return _resolution;
}

const std::tuple<int, int, int> &RayTracer::Camera::Camera::getRotation() const
{
    return _rotation;
}

const RayTracer::Math::Color &RayTracer::Camera::Camera::getBackground() const
{
    return _background;
}

const RayTracer::Math::Point3D &RayTracer::Camera::Camera::getOrigin() const
{
    return _origin;
}

const RayTracer::Camera::Screen &RayTracer::Camera::Camera::getScreen() const
{
    return _screen;
}

void RayTracer::Camera::Camera::setAspectRatio(double aspectRatio)
{
    _aspectRatio = aspectRatio;
}

void RayTracer::Camera::Camera::setFocalLength(double focalLength)
{
    _focalLength = focalLength;
}

void RayTracer::Camera::Camera::setFov(double fov)
{
    _fov = fov;
}

void RayTracer::Camera::Camera::setViewportHeight(double viewportHeight)
{
    _viewportHeight = viewportHeight;
}

void RayTracer::Camera::Camera::setViewportWidth(double viewportWidth)
{
    _viewportWidth = viewportWidth;
}

void RayTracer::Camera::Camera::setResolution(const std::tuple<int, int> &resolution)
{
    _resolution = resolution;
}

void RayTracer::Camera::Camera::setRotation(const std::tuple<int, int, int> &rotation)
{
    _rotation = rotation;
}

void RayTracer::Camera::Camera::setBackground(const RayTracer::Math::Color &background)
{
    _background = background;
}

void RayTracer::Camera::Camera::setOrigin(const RayTracer::Math::Point3D &origin)
{
    _origin = origin;
}

void RayTracer::Camera::Camera::setScreen(const RayTracer::Camera::Screen &screen)
{
    _screen = screen;
}

/* Methods */

RayTracer::Ray RayTracer::Camera::Camera::ray(double u, double v) const
{
    RayTracer::Math::Vector3D rd = _lensRadius * RayTracer::Math::Vector3D::randomInUnitDisk();
    RayTracer::Math::Vector3D offset = _u * rd.getX() + _v * rd.getY();

    RayTracer::Math::Point3D off(offset.getX(), offset.getY(), offset.getZ());

    RayTracer::Math::Point3D screenPoint(_screen.getOrigin());
    screenPoint += u * _screen.getHorizontal();
    screenPoint += v * _screen.getVertical();
    screenPoint -= _origin;
    screenPoint -= off;

    RayTracer::Math::Vector3D screenVector(screenPoint.getX(), screenPoint.getY(), screenPoint.getZ());

    return RayTracer::Ray(_origin + off, screenVector, randomDouble(_time0, _time1));
}
