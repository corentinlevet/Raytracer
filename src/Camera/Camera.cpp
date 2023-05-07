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

RayTracer::Camera::Camera::Camera(double fov, std::tuple<int, int> resolution, std::tuple<int, int, int> rotation, const RayTracer::Math::Point3D &origin, const RayTracer::Camera::Rectangle &screen) : _fov(fov), _resolution(resolution), _rotation(rotation), _origin(origin), _screen(screen)
{
    _aspectRatio = 16.0 / 9.0;
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

const RayTracer::Math::Point3D &RayTracer::Camera::Camera::getOrigin() const
{
    return _origin;
}

const RayTracer::Camera::Rectangle &RayTracer::Camera::Camera::getScreen() const
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

void RayTracer::Camera::Camera::setOrigin(const RayTracer::Math::Point3D &origin)
{
    _origin = origin;
}

void RayTracer::Camera::Camera::setScreen(const RayTracer::Camera::Rectangle &rectangle)
{
    _screen = rectangle;
}

/* Methods */

RayTracer::Ray RayTracer::Camera::Camera::ray(double u, double v) const
{
    RayTracer::Math::Point3D screenPoint(_screen.getOrigin());
    screenPoint += u * _screen.getHorizontal();
    screenPoint += v * _screen.getVertical();
    screenPoint -= _origin;
    RayTracer::Math::Vector3D screenVector(screenPoint.getX(), screenPoint.getY(), screenPoint.getZ());
    return RayTracer::Ray(_origin, screenVector);
}
