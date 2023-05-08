/*
** EPITECH PROJECT, 2022
** Parser.cpp
** File description:
** Source file for the Parser class
*/

#include "Parser.hpp"

#include "Camera.hpp"
#include "FormList.hpp"
#include "FormFactory.hpp"
#include "MaterialFactory.hpp"

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

RayTracer::Camera::Camera RayTracer::Parser::getCamera(RayTracer::Camera::Camera &cam)
{
    int width = _config.lookup("camera.resolution.width"), height = _config.lookup("camera.resolution.height");
    int positionX = _config.lookup("camera.position.x"), positionY = _config.lookup("camera.position.y"), positionZ = _config.lookup("camera.position.z");
    int rotationX = _config.lookup("camera.rotation.x"), rotationY = _config.lookup("camera.rotation.y"), rotationZ = _config.lookup("camera.rotation.z");
    double fov = _config.lookup("camera.fieldOfView");

    RayTracer::Math::Point3D origin(positionX, positionY, positionZ);
    RayTracer::Math::Vector3D horizontal(cam.getViewportWidth(), 0, 0);
    RayTracer::Math::Vector3D vertical(0, cam.getViewportHeight(), 0);
    RayTracer::Math::Vector3D orig(origin.getX(), origin.getY(), origin.getZ());
    RayTracer::Math::Vector3D lowerLeftCorner = orig - horizontal / 2 - vertical / 2 - RayTracer::Math::Vector3D(0, 0, cam.getFocalLength());

    RayTracer::Camera::Camera camera(
        fov,
        std::tuple<int, int>(width, height),
        std::tuple<int, int, int>(rotationX, rotationY, rotationZ),
        RayTracer::Math::Point3D(positionX, positionY, positionZ),
        RayTracer::Camera::Rectangle(Math::Point3D(lowerLeftCorner.getX(), lowerLeftCorner.getY(), lowerLeftCorner.getZ()), horizontal, vertical)
    );

    return camera;
}

MaterialPtr RayTracer::Parser::getMaterial(const libconfig::Setting &material)
{
    MaterialPtr newMaterial = nullptr;
    std::string materialName = material.lookup("name");
    newMaterial = MaterialFactory::createMaterial(materialName);
    float materialR = 0, materialG = 0, materialB = 0, fuzziness = 0, refractionIndex = 0;
    libconfig::Setting &albedo = material.lookup("albedo");
    albedo.lookupValue("r", materialR);
    albedo.lookupValue("g", materialG);
    albedo.lookupValue("b", materialB);
    material.lookupValue("fuzziness", fuzziness);
    material.lookupValue("refractionIndex", refractionIndex);
    newMaterial->setAlbedo(Math::Color(materialR, materialG, materialB));
    newMaterial->setFuzziness(fuzziness);
    newMaterial->setRefractionIndex(refractionIndex);
    return newMaterial;
}

FormPtr RayTracer::Parser::getForm(const std::string &name, const libconfig::Setting &form)
{
    FormPtr newForm = nullptr;
    int colorR = 0, colorG = 0, colorB = 0;
    form.lookupValue("color.r", colorR);
    form.lookupValue("color.g", colorG);
    form.lookupValue("color.b", colorB);
    if (name == "spheres") {
        float sphereX = 0, sphereY = 0, sphereZ = 0, sphereRadius = 0;
        form.lookupValue("x", sphereX);
        form.lookupValue("y", sphereY);
        form.lookupValue("z", sphereZ);
        form.lookupValue("r", sphereRadius);
        newForm = FormFactory::createForm("Sphere");
        newForm->setCenter(Math::Point3D(sphereX, sphereY, sphereZ));
        newForm->setRadius((double) sphereRadius);
        newForm->setColor(Math::Color(colorR, colorG, colorB));
        if (form.exists("material"))
            newForm->setMaterial(getMaterial(form.lookup("material")));
    }

    return newForm;
}

RayTracer::Forms::FormList RayTracer::Parser::getWorld()
{
    RayTracer::Forms::FormList world;
    FormPtr form = nullptr;
    MaterialPtr material = nullptr;

    for (auto &p : _config.lookup("primitives")) {
        std::string name = p.getName();
        for (auto &f : _config.lookup("primitives." + name)) {
            form = getForm(name, f);
            if (form != nullptr) {
                world.add(form);
                form = nullptr;
                material = nullptr;
            }
        }
    }

    return world;
}
