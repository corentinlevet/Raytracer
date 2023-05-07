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

#endif /* !RANDOM_HPP_ */
