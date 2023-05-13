/*
** EPITECH PROJECT, 2022
** Raytracer.hpp
** File description:
** Header file for the Raytracer class
*/

#pragma once

#ifndef RAYTRACER_HPP_
    #define RAYTRACER_HPP_

    #include <fstream>
    #include <iostream>

    #include "Camera.hpp"
    #include "FormList.hpp"
    #include "SFML.hpp"

    namespace RayTracer {
        class Raytracer {
            public:
                Raytracer(const std::string &sceneFile);
                ~Raytracer() = default;

                void run();

                /* Scenes */
                RayTracer::Forms::FormList randomScene();
                RayTracer::Forms::FormList finalScene();

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
                std::string _sceneFile;

                RayTracer::Camera::Camera _camera;

                RayTracer::Forms::FormList _world;

                RayTracer::SFML _sfml;
        };
    }

#endif /* !RAYTRACER_HPP_ */
