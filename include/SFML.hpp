/*
** EPITECH PROJECT, 2022
** SFML.hpp
** File description:
** Header file for the SFML class
*/

#pragma once

#ifndef SFML_HPP_
    #define SFML_HPP_

    #include <memory>
    #include <vector>

    #include <SFML/Graphics.hpp>

    #include "Color.hpp"

    namespace RayTracer {
        class SFML {
            public:
                /* Constructor & Destructor */
                SFML();
                ~SFML();


                /* Getters & Setters */
                bool isWindowOpen() const {
                    return _isWindowOpen;
                }

                /* Methods */
                void initWindow(int width, int height);

                void printPixels(std::vector<RayTracer::Math::Color> pixelColors, int width, int y, int samplesPerPixel);

            private:
                bool _isWindowOpen;

                sf::RenderWindow _window;

                std::vector<sf::Vertex> _pixels;
        };
    }

#endif /* !SFML_HPP_ */
