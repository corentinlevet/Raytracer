/*
** EPITECH PROJECT, 2023
** Raypisseur
** File description:
** Sfml
*/

#ifndef SFML_HPP_
    #define SFML_HPP_

    #include "Color.hpp"
    #include <SFML/Graphics.hpp>
    #include <vector>

namespace RayTracer {
    class Sfml {
        public:
            Sfml();
            ~Sfml();

            void initWindow(int width, int height);
            void printPixel(RayTracer::Math::Color pixelColor);

            int getWidth();
            int getHeight();

            void setWidth(int width);
            void setHeight(int height);

            void display();

        protected:
            int _width;
            int _height;
            int _x;
            int _y;
            sf::RenderWindow _window;
            sf::Texture _texture;
            std::vector<sf::Vertex> _pixels;
            std::vector<RayTracer::Math::Color> _ColorPixels;
    };
}

#endif /* !SFML_HPP_ */
