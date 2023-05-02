/*
** EPITECH PROJECT, 2022
** Camera.hpp
** File description:
** Header file for the Camera class
*/

#pragma once

#ifndef CAMERA_HPP_
    #define CAMERA_HPP_

    #include "Ray.hpp"

    #include "Rectangle.hpp"

    namespace RayTracer::Camera {
        class Camera {
            public:
                Camera(const Math::Point3D &origin = Math::Point3D(), const RayTracer::Camera::Rectangle &rectangle = RayTracer::Camera::Rectangle(Math::Point3D(), Math::Vector3D(1, 0), Math::Vector3D(0, 1)));
                ~Camera() = default;

                /* Getters and setters */

                const Math::Point3D &getOrigin() const;
                const RayTracer::Camera::Rectangle &getScreen() const;

                void setOrigin(const Math::Point3D &origin);
                void setScreen(const RayTracer::Camera::Rectangle &rectangle);

                /* Methods */

                RayTracer::Ray ray(double u, double v) const;

            private:
                Math::Point3D _origin;
                RayTracer::Camera::Rectangle _screen;
        };
    }

#endif /* !CAMERA_HPP_ */
