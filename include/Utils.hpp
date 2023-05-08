/*
** EPITECH PROJECT, 2022
** Utils.hpp
** File description:
** Header file for the Utils variables and functions
*/

#pragma once

#ifndef UTILS_HPP_
    #define UTILS_HPP_

    #include <limits>

    const double infinity = std::numeric_limits<double>::infinity();
    const double pi = 3.1415926535897932385;

    inline double degreesToRadians(double degrees) {
        return degrees * pi / 180;
    }

#endif /* !UTILS_HPP_ */
