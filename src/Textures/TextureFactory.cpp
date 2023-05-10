/*
** EPITECH PROJECT, 2022
** TextureFactory.cpp
** File description:
** Source file for the TextureFactory class
*/

#include "TextureFactory.hpp"

TexturePtr RayTracer::Textures::TextureFactory::createTexture(const std::string &name)
{
    std::map<std::string, std::string> paths = {
        {"Checker", "libs/Textures/Checker.so"},
        {"SolidColor", "libs/Textures/SolidColor.so"},
    };

    TexturePtr library = DLLoader::loadLibrary<RayTracer::Textures::ITexture>(paths.at(name), "Texture");

    return library;
}
