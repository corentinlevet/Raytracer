/*
** EPITECH PROJECT, 2022
** Raytracer.hpp
** File description:
** Header file for the Raytracer class
*/

#pragma once

#ifndef RAYTRACER_HPP_
    #define RAYTRACER_HPP_

    #include "Parser.hpp"

    #include <iostream>

    namespace RayTracer {
        class Raytracer {
            public:
                Raytracer(const std::string &sceneFile);
                ~Raytracer() = default;

                void run();

                class softError : public Error {
                    public:
                        softError(const std::string &where, const std::string &what) : Error("RayTracer::Raytracer::" + where, what) {}
                        ~softError() = default;
                };

                class hardError : public Error {
                    public:
                        hardError(const std::string &where, const std::string &what) : Error("RayTracer::Raytracer::" + where, what) {}
                        ~hardError() = default;
                };

            private:
                std::vector<FormPtr> _forms;

                RayTracer::Camera::Camera _camera;
        };
    }

#endif /* !RAYTRACER_HPP_ */
