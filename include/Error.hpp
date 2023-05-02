/*
** EPITECH PROJECT, 2022
** Error.hpp
** File description:
** Header file for the Error class
*/

#pragma once

#ifndef ERROR_HPP_
    #define ERROR_HPP_

    #include <string>

    namespace RayTracer {
        class Error : public std::exception {
            public:
                Error(const std::string &where, const std::string &what) : _where(where), _what(what) {}
                ~Error() = default;

                const char *what() const noexcept override { return _what.c_str(); }
                const char *where() const noexcept { return _where.c_str(); }

            private:
                std::string _where;
                std::string _what;
        };
    }

#endif /* !ERROR_HPP_ */
