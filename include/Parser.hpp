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
    #include <memory>
    #include <vector>

    #include "Error.hpp"

    namespace RayTracer {
        namespace Camera {
            class Camera;
        }

        namespace Forms {
            class FormList;
            class IForm;
        }

        namespace Materials {
            class IMaterial;
        }

        namespace Textures {
            class ITexture;
        }
    }

    typedef std::shared_ptr<RayTracer::Forms::IForm> FormPtr;
    typedef std::shared_ptr<RayTracer::Materials::IMaterial> MaterialPtr;
    typedef std::shared_ptr<RayTracer::Textures::ITexture> TexturePtr;

    namespace RayTracer {
        class Parser {
            public:
                Parser(const std::string &path);
                ~Parser() = default;

                Camera::Camera getCamera(RayTracer::Camera::Camera &camera);
                Forms::FormList getWorld();
                FormPtr getForm(const std::string &name, const libconfig::Setting &form);
                void getTransformations(FormPtr &form, const libconfig::Setting &transformations);
                MaterialPtr getMaterial(const libconfig::Setting &material);
                TexturePtr getTexture(const libconfig::Setting &texture);

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
