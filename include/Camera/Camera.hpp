/*
** EPITECH PROJECT, 2022
** Camera.hpp
** File description:
** Header file for the Camera class
*/

#pragma once

#ifndef CAMERA_HPP_
    #define CAMERA_HPP_

    #include "Rectangle.hpp"

    namespace RayTracer {
        class Ray;
    }

    namespace RayTracer::Camera {
        class Camera {
            public:
                Camera(
                    double aperture = 0.0,
                    double aspectRatio = 16.0 / 9.0,
                    double fov = 90.0,
                    std::tuple<int, int> resolution = std::tuple<int, int>(1920, 1080),
                    std::tuple<int, int, int> rotation = std::tuple<int, int, int>(0, 0, 0),
                    const Math::Point3D &origin = Math::Point3D(),
                    const RayTracer::Camera::Rectangle &screen = RayTracer::Camera::Rectangle(Math::Point3D(), Math::Vector3D(1, 0), Math::Vector3D(0, 1)),
                    const RayTracer::Math::Vector3D u = Math::Vector3D(),
                    const RayTracer::Math::Vector3D v = Math::Vector3D(),
                    const RayTracer::Math::Vector3D w = Math::Vector3D()
                );
                ~Camera() = default;

                /* Getters and setters */

                double getAspectRatio() const;
                double getFocalLength() const;
                double getFov() const;
                double getViewportHeight() const;
                double getViewportWidth() const;
                const std::tuple<int, int> &getResolution() const;
                const std::tuple<int, int, int> &getRotation() const;
                const Math::Point3D &getOrigin() const;
                const RayTracer::Camera::Rectangle &getScreen() const;

                void setAspectRatio(double aspectRatio);
                void setFocalLength(double focalLength);
                void setFov(double fov);
                void setViewportHeight(double viewportHeight);
                void setViewportWidth(double viewportWidth);
                void setResolution(const std::tuple<int, int> &resolution);
                void setRotation(const std::tuple<int, int, int> &rotation);
                void setOrigin(const Math::Point3D &origin);
                void setScreen(const RayTracer::Camera::Rectangle &rectangle);

                /* Methods */

                RayTracer::Ray ray(double u, double v) const;

            private:
                double _aspectRatio;
                double _focalLength;
                double _fov;
                double _lensRadius;
                double _viewportHeight;
                double _viewportWidth;

                std::tuple<int, int> _resolution;
                std::tuple<int, int, int> _rotation;

                RayTracer::Math::Point3D _origin;
                RayTracer::Camera::Rectangle _screen;

                RayTracer::Math::Vector3D _u;
                RayTracer::Math::Vector3D _v;
                RayTracer::Math::Vector3D _w;
        };
    }

#endif /* !CAMERA_HPP_ */
