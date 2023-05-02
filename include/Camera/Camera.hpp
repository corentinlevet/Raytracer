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
                Camera(const Math::Point3D &origin = Math::Point3D(), const RayTracer::Camera::Rectangle &rectangle = RayTracer::Camera::Rectangle());
                ~Camera() = default;

                /* Getters and setters */

                const Math::Point3D &getOrigin() const;
                const RayTracer::Camera::Rectangle &getRectangle() const;

                void setOrigin(const Math::Point3D &origin);
                void setRectangle(const RayTracer::Camera::Rectangle &rectangle);

                /* Methods */

                RayTracer::Ray ray(double u, double v) const;

            private:
                Math::Point3D _origin;
                RayTracer::Camera::Rectangle _rectangle;
        };
    }

#endif /* !CAMERA_HPP_ */
