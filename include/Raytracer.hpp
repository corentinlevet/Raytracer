/*
** EPITECH PROJECT, 2022
** Raytracer.hpp
** File description:
** Header file for the Raytracer class
*/

#pragma once

#ifndef RAYTRACER_HPP_
    #define RAYTRACER_HPP_

    #include "Error.hpp"

    #include <fstream>
    #include <iostream>

    namespace Raytracer {
        class Raytracer {
            public:
                Raytracer(const std::string &sceneFile);
                ~Raytracer() = default;

                void run();

                class softError : public Error {
                    public:
                        softError(const std::string &where, const std::string &what) : Error("Raytracer::Raytracer::" + where, what) {}
                        ~softError() = default;
                };

                class hardError : public Error {
                    public:
                        hardError(const std::string &where, const std::string &what) : Error("Raytracer::Raytracer::" + where, what) {}
                        ~hardError() = default;
                };

            private:
                std::string _sceneFile;
        };
    }

#endif /* !RAYTRACER_HPP_ */