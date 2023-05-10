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
        static std::uniform_real_distribution<double> distribution(min, max);
        static std::mt19937 generator(std::random_device{}());
        return distribution(generator);
    }

    inline int randomInt(int min = 0, int max = 1) {
        return static_cast<int>(randomDouble(min, max + 1));
    }

#endif /* !RANDOM_HPP_ */
