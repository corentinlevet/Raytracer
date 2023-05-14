/*
** EPITECH PROJECT, 2022
** Camera.hpp
** File description:
** Header file for the Camera class
*/

#pragma once

#ifndef CAMERA_HPP_
    #define CAMERA_HPP_

    #include "Screen.hpp"
    #include <tuple>

    namespace RayTracer {
        class Ray;
    }

    namespace RayTracer::Camera {
        class Camera {
            public:
                Camera(
                    const bool upscale = false,
                    const int samplesPerPixel = 128,
                    const double aperture = 0.0,
                    const double aspectRatio = 16.0 / 9.0,
                    const double fov = 90.0,
                    const double time0 = 0.0,
                    const double time1 = 0.0,
                    std::tuple<int, int> resolution = std::tuple<int, int>(1920, 1080),
                    std::tuple<int, int, int> rotation = std::tuple<int, int, int>(0, 0, 0),
                    const RayTracer::Math::Color &background = RayTracer::Math::Color(0.0, 0.0, 0.0),
                    const Math::Point3D &origin = Math::Point3D(),
                    const RayTracer::Camera::Screen &screen = RayTracer::Camera::Screen(Math::Point3D(), Math::Vector3D(1, 0), Math::Vector3D(0, 1)),
                    const RayTracer::Math::Vector3D u = Math::Vector3D(),
                    const RayTracer::Math::Vector3D v = Math::Vector3D(),
                    const RayTracer::Math::Vector3D w = Math::Vector3D()
                );
                ~Camera() = default;

                /* Getters and setters */

                bool getUpscale() const;
                int getSamplesPerPixel() const;
                double getAspectRatio() const;
                double getFocalLength() const;
                double getFov() const;
                double getViewportHeight() const;
                double getViewportWidth() const;
                const std::tuple<int, int> &getResolution() const;
                const std::tuple<int, int, int> &getRotation() const;
                const RayTracer::Math::Color &getBackground() const;
                const Math::Point3D &getOrigin() const;
                const RayTracer::Camera::Screen &getScreen() const;

                void setUpscale(bool upscale);
                void setSamplesPerPixel(int samplesPerPixel);
                void setAspectRatio(double aspectRatio);
                void setFocalLength(double focalLength);
                void setFov(double fov);
                void setViewportHeight(double viewportHeight);
                void setViewportWidth(double viewportWidth);
                void setResolution(const std::tuple<int, int> &resolution);
                void setRotation(const std::tuple<int, int, int> &rotation);
                void setBackground(const RayTracer::Math::Color &background);
                void setOrigin(const Math::Point3D &origin);
                void setScreen(const RayTracer::Camera::Screen &screen);

                /* Methods */

                RayTracer::Ray ray(double u, double v) const;

            private:
                bool _upscale;

                int _samplesPerPixel;

                double _aspectRatio;
                double _focalLength;
                double _fov;
                double _lensRadius;
                double _time0;
                double _time1;
                double _viewportHeight;
                double _viewportWidth;

                std::tuple<int, int> _resolution;
                std::tuple<int, int, int> _rotation;

                RayTracer::Math::Color _background;

                RayTracer::Math::Point3D _origin;
                RayTracer::Camera::Screen _screen;

                RayTracer::Math::Vector3D _u;
                RayTracer::Math::Vector3D _v;
                RayTracer::Math::Vector3D _w;
        };
    }

#endif /* !CAMERA_HPP_ */
