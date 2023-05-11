/*
** EPITECH PROJECT, 2022
** Screen.hpp
** File description:
** Header file for the Screen class
*/

#pragma once

#ifndef SCREEN_HPP_
    #define SCREEN_HPP_

    #include "Error.hpp"

    #include "Point3D.hpp"

    namespace RayTracer::Camera {
        class Screen {
            public:
                Screen(const Math::Point3D &origin = Math::Point3D(), const Math::Vector3D &bottomSide = Math::Vector3D(), const Math::Vector3D &leftSide = Math::Vector3D());
                ~Screen() = default;

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
                        softError(const std::string &where, const std::string &what) : Error("RayTracer::Camera::Screen::" + where, what) {}
                };

            private:
                Math::Point3D _origin;
                Math::Vector3D _bottomSide;
                Math::Vector3D _leftSide;
        };
    }

#endif /* !SCREEN_HPP_ */