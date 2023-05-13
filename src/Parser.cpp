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
#include "TextureFactory.hpp"

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
    int directionX = _config.lookup("camera.direction.x"), directionY = _config.lookup("camera.direction.y"), directionZ = _config.lookup("camera.direction.z");
    double fov = _config.lookup("camera.fieldOfView");
    double aspectRatioX = _config.lookup("camera.aspectRatio.width"), aspectRatioY = _config.lookup("camera.aspectRatio.height");
    double aspectRatio = aspectRatioX / aspectRatioY;
    double aperture = _config.lookup("camera.aperture");
    double backgroundR = _config.lookup("camera.background.r"), backgroundG = _config.lookup("camera.background.g"), backgroundB = _config.lookup("camera.background.b");

    double theta = degreesToRadians(fov);
    double h = tan(theta / 2);
    double viewportHeight = 2.0 * h;
    double viewportWidth = cam.getAspectRatio() * viewportHeight;

    RayTracer::Math::Point3D origin(positionX, positionY, positionZ);
    RayTracer::Math::Vector3D orig(origin.getX(), origin.getY(), origin.getZ());
    RayTracer::Math::Vector3D lookAt(directionX, directionY, directionZ);

    auto focusDist = (orig - lookAt).length();

    auto w = unitVector(orig - lookAt);
    auto u = unitVector(cross(RayTracer::Math::Vector3D(0, 1, 0), w));
    auto v = cross(w, u);

    RayTracer::Math::Vector3D horizontal(focusDist * viewportWidth * u.getX(), focusDist * viewportWidth * u.getY(), focusDist * viewportWidth * u.getZ());
    RayTracer::Math::Vector3D vertical(focusDist * viewportHeight * v.getX(), focusDist * viewportHeight * v.getY(), focusDist * viewportHeight * v.getZ());
    RayTracer::Math::Vector3D lowerLeftCorner = orig - horizontal / 2 - vertical / 2 - focusDist * w;

    RayTracer::Camera::Camera camera(
        aperture,
        aspectRatio,
        fov,
        0,
        0,
        std::tuple<int, int>(width, height),
        std::tuple<int, int, int>(directionX, directionY, directionZ),
        RayTracer::Math::Color(backgroundR, backgroundG, backgroundB),
        origin,
        RayTracer::Camera::Screen(Math::Point3D(lowerLeftCorner.getX(), lowerLeftCorner.getY(), lowerLeftCorner.getZ()), horizontal, vertical),
        u,
        v,
        w
    );

    camera.setViewportHeight(viewportHeight);
    camera.setViewportWidth(viewportWidth);

    return camera;
}

TexturePtr RayTracer::Parser::getTexture(const libconfig::Setting &texture)
{
    TexturePtr newTexture = nullptr;
    std::string textureName = texture.lookup("name");
    if (textureName == "Checker") {
        newTexture = TextureFactory::createTexture("Checker");
        auto &color1 = texture.lookup("properties.color1");
        auto &color2 = texture.lookup("properties.color2");
        float color1R = 0, color1G = 0, color1B = 0, color2R = 0, color2G = 0, color2B = 0;
        color1.lookupValue("r", color1R); color1.lookupValue("g", color1G); color1.lookupValue("b", color1B);
        color2.lookupValue("r", color2R); color2.lookupValue("g", color2G); color2.lookupValue("b", color2B);
        auto Color1 = TextureFactory::createTexture("SolidColor");
        auto Color2 = TextureFactory::createTexture("SolidColor");
        Color1->setColor(Math::Color(color1R, color1G, color1B));
        Color2->setColor(Math::Color(color2R, color2G, color2B));
        newTexture->setTextureOdd(Color1);
        newTexture->setTextureEven(Color2);
    } else if (textureName == "Perlin") {
        newTexture = TextureFactory::createTexture("Perlin");
        auto &properties = texture.lookup("properties");
        float scale = 0;
        properties.lookupValue("scale", scale);
        newTexture->setScale(scale);
    } else if (textureName == "Image") {
        newTexture = TextureFactory::createTexture("Image");
        auto &properties = texture.lookup("properties");
        std::string path = properties.lookup("path");
        newTexture->setPath(path);
    }
    return newTexture;
}

MaterialPtr RayTracer::Parser::getMaterial(const libconfig::Setting &material)
{
    MaterialPtr newMaterial = nullptr;
    std::string materialName = material.lookup("name");
    newMaterial = MaterialFactory::createMaterial(materialName);
    float materialR = 0, materialG = 0, materialB = 0, fuzziness = 0, refractionIndex = 0;
    libconfig::Setting &albedo = material.lookup("albedo");
    albedo.lookupValue("r", materialR); albedo.lookupValue("g", materialG); albedo.lookupValue("b", materialB);
    material.lookupValue("fuzziness", fuzziness);
    material.lookupValue("refractionIndex", refractionIndex);
    newMaterial->setAlbedo(Math::Color(materialR, materialG, materialB));
    newMaterial->setFuzziness(fuzziness);
    newMaterial->setRefractionIndex(refractionIndex);
    if (material.exists("texture")) {
        TexturePtr texture = getTexture(material.lookup("texture"));
        newMaterial->setTexture(texture);
    } else
        newMaterial->setTexture(nullptr);
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
        form.lookupValue("radius", sphereRadius);
        newForm = FormFactory::createForm("Sphere");
        newForm->setCenter(Math::Point3D(sphereX, sphereY, sphereZ));
        newForm->setRadius((double) sphereRadius);
        newForm->setColor(Math::Color(colorR, colorG, colorB));
        if (form.exists("material")) {
            MaterialPtr material = getMaterial(form.lookup("material"));
            newForm->setMaterial(material);
        } else
            newForm->setMaterial(nullptr);
    }

    return newForm;
}

RayTracer::Forms::FormList RayTracer::Parser::getWorld()
{
    RayTracer::Forms::FormList world;
    FormPtr form = nullptr;

    for (auto &p : _config.lookup("primitives")) {
        std::string name = p.getName();
        for (auto &f : _config.lookup("primitives." + name)) {
            form = getForm(name, f);
            if (form != nullptr) {
                world.add(form);
                form = nullptr;
            }
        }
    }

    return world;
}
