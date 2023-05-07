/*
** EPITECH PROJECT, 2022
** Random.hpp
** File description:
** Header file for Random utilities
*/

#pragma once

#ifndef RANDOM_HPP_
    #define RANDOM_HPP_

    #include <random>

    inline double randomDouble(double min = 0.0, double max = 1.0) {
        std::uniform_real_distribution<> dis(min, max);
        std::mt19937 gen;

        return dis(gen);
    }

#endif /* !RANDOM_HPP_ */
