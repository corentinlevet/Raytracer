/*
** EPITECH PROJECT, 2022
** Parser.cpp
** File description:
** Source file for the Parser class
*/

#include "Parser.hpp"

#include <iostream>

/* Constructors and destructors */

RayTracer::Parser::Parser(const std::string &path)
{
    try {
        _config.readFile(path.c_str());
    } catch (const libconfig::FileIOException &e) {
        throw hardError("Parser", "Couldn't read file '" + path + "'");
    } catch (const libconfig::ParseException &e) {
        throw hardError("Parser", "Parse error at " + std::to_string(e.getLine()) + ": " + e.getError());
    }
}

/* Public methods */

RayTracer::Camera::Camera RayTracer::Parser::getCamera()
{
    int width = _config.lookup("camera.resolution.width"), height = _config.lookup("camera.resolution.height");
    int positionX = _config.lookup("camera.position.x"), positionY = _config.lookup("camera.position.y"), positionZ = _config.lookup("camera.position.z");
    int rotationX = _config.lookup("camera.rotation.x"), rotationY = _config.lookup("camera.rotation.y"), rotationZ = _config.lookup("camera.rotation.z");
    double fov = _config.lookup("camera.fieldOfView");

    RayTracer::Camera::Camera camera(
        RayTracer::Math::Point3D(positionX, positionY, positionZ),
        RayTracer::Camera::Rectangle(Math::Point3D(), Math::Vector3D(1, 0), Math::Vector3D(0, 1)),
        std::tuple<int, int>(width, height),
        std::tuple<int, int, int>(rotationX, rotationY, rotationZ),
        fov
    );

    return camera;
}

std::vector<FormPtr> RayTracer::Parser::getForms()
{
    std::vector<FormPtr> forms = {};
    FormPtr form = nullptr;

    for (auto &p : _config.lookup("primitives")) {
        std::string name = p.getName();
        for (auto &f : _config.lookup("primitives." + name)) {
            if (name == "spheres") {
                libconfig::Setting &s = f;
                int sphereColorR = s.lookup("color.r"), sphereColorG = s.lookup("color.g"), sphereColorB = s.lookup("color.b");
                int sphereX = s.lookup("x"), sphereY = s.lookup("y"), sphereZ = s.lookup("z");
                int sphereRadius = s.lookup("r");
                form = FormFactory::createForm("Sphere");
                form->setCenter(Math::Point3D(sphereX, sphereY, sphereZ));
                form->setRadius((double) sphereRadius);
                form->setColor(std::make_tuple(sphereColorR, sphereColorG, sphereColorB));
            }
            if (form != nullptr) {
                forms.push_back(std::move(form));
                form = nullptr;
            }
        }
    }

    return forms;
}
