/*
** EPITECH PROJECT, 2022
** Parser.hpp
** File description:
** Header file for the Parser class
*/

#pragma once

#ifndef PARSER_HPP_
    #define PARSER_HPP_

    #include <libconfig.h++>
    #include <vector>

    #include "Error.hpp"

    #include "Camera.hpp"

    #include "FormFactory.hpp"

    namespace RayTracer {
        class Parser {
            public:
                Parser(const std::string &path);
                ~Parser() = default;

                Camera::Camera getCamera();
                std::vector<FormPtr> getForms();

                class hardError : public Error {
                    public:
                        hardError(const std::string &where, const std::string &what) : Error("RayTracer::Parser::" + where, what) {}
                        ~hardError() = default;
                };

            private:
                libconfig::Config _config;
        };
    }

#endif /* !PARSER_HPP_ */
