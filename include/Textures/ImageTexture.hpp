/*
** EPITECH PROJECT, 2022
** ImageTexture.hpp
** File description:
** Header file for the ImageTexture class
*/

#pragma once

#ifndef IMAGETEXTURE_HPP_
    #define IMAGETEXTURE_HPP_

    #include "ATexture.hpp"

    #define STB_IMAGE_IMPLEMENTATION
    #include <stb_image.h>

    namespace RayTracer::Textures {
        class ImageTexture : public ATexture {
            public:
                ImageTexture();
                ImageTexture(const std::string &path);
                ~ImageTexture() = default;

                /* Getters and setters */

                RayTracer::Math::Color getColor() const {
                    return RayTracer::Math::Color();
                }

                void setColor(const RayTracer::Math::Color &color) {
                    (void)color;
                }

                void setTextureOdd(const std::shared_ptr<ITexture> &texture) {
                    (void)texture;
                }

                void setTextureEven(const std::shared_ptr<ITexture> &texture) {
                    (void)texture;
                }

                void setScale(double scale) {
                    (void)scale;
                }

                /* Methods */

                void setPath(const std::string &path);

                RayTracer::Math::Color value(double u, double v, const RayTracer::Math::Point3D &p) const;

            private:
                unsigned char *_data;

                int _bytesPerScanline;
                int _height;
                int _width;
        };
    }

    extern "C"
    {
        TexturePtr entryPointTexture();
    }

#endif /* !IMAGETEXTURE_HPP_ */
