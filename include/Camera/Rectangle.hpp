/*
** EPITECH PROJECT, 2022
** Rectangle.hpp
** File description:
** Header file for the Rectangle class
*/

#pragma once

#ifndef RECTANGLE_HPP_
    #define RECTANGLE_HPP_

    #include "Error.hpp"

    #include "Point3D.hpp"

    namespace RayTracer::Camera {
        class Rectangle {
            public:
                Rectangle(const Math::Point3D &origin = Math::Point3D(), const Math::Vector3D &bottomSide = Math::Vector3D(), const Math::Vector3D &leftSide = Math::Vector3D());
                ~Rectangle() = default;

                /* Getters and setters */

                const Math::Point3D &getOrigin() const;
                const Math::Vector3D &getHorizontal() const;
                const Math::Vector3D &getVertical() const;

                void setOrigin(const Math::Point3D &origin);
                void setBottomSide(const Math::Vector3D &bottomSide);
                void setLeftSide(const Math::Vector3D &leftSide);

                /* Methods */

                Math::Point3D pointAt(double u, double v) const;

                class softError : public Error {
                    public:
                        softError(const std::string &where, const std::string &what) : Error("RayTracer::Camera::Rectangle::" + where, what) {}
                };

            private:
                Math::Point3D _origin;
                Math::Vector3D _bottomSide;
                Math::Vector3D _leftSide;
        };
    }

#endif /* !RECTANGLE_HPP_ */