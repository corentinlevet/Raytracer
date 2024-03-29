/*
** EPITECH PROJECT, 2022
** Parser.cpp
** File description:
** Source file for the Parser class
*/

#include "Parser.hpp"

#include "BVHNode.hpp"
#include "Camera.hpp"
#include "FormList.hpp"
#include "FormFactory.hpp"
#include "LightFactory.hpp"
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
    int samplesPerPixel = _config.lookup("camera.samplesPerPixel");
    int up = _config.lookup("camera.upscale");
    bool upscale = up == 1 ? true : false;

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
        upscale,
        samplesPerPixel,
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
    } else if (textureName == "SolidColor") {
        newTexture = TextureFactory::createTexture("SolidColor");
        auto &color = texture.lookup("properties.color");
        float r = 0, g = 0, b = 0;
        color.lookupValue("r", r); color.lookupValue("g", g); color.lookupValue("b", b);
        newTexture->setColor(Math::Color(r, g, b));
    }
    return newTexture;
}

MaterialPtr RayTracer::Parser::getMaterial(const libconfig::Setting &material)
{
    MaterialPtr newMaterial = nullptr;
    std::string materialName = material.lookup("name");
    std::string materialType = material.lookup("type");
    if (materialType == "Material") {
        newMaterial = MaterialFactory::createMaterial(materialName);
        if (material.exists("albedo")) {
            float materialR = 0, materialG = 0, materialB = 0;
            const libconfig::Setting &albedo = material.lookup("albedo");
            albedo.lookupValue("r", materialR); albedo.lookupValue("g", materialG); albedo.lookupValue("b", materialB);
            newMaterial->setAlbedo(Math::Color(materialR, materialG, materialB));
        }
        if (material.exists("fuzziness")) {
            float fuzziness = 0;
            material.lookupValue("fuzziness", fuzziness);
            newMaterial->setFuzziness(fuzziness);
        }
        if (material.exists("refractionIndex")) {
            float refractionIndex = 0;
            material.lookupValue("refractionIndex", refractionIndex);
            newMaterial->setRefractionIndex(refractionIndex);
        }
    } else if (materialType == "Light") {
        newMaterial = LightFactory::createLight(materialName);
    }
    if (material.exists("texture")) {
        TexturePtr texture = getTexture(material.lookup("texture"));
        newMaterial->setTexture(texture);
    } else
        newMaterial->setTexture(nullptr);
    return newMaterial;
}

void RayTracer::Parser::getTransformations(FormPtr &form, const libconfig::Setting &transformations)
{
    for (auto &t : transformations) {
        std::string transformationName = t.lookup("type");
        if (transformationName == "Translate") {
            FormPtr translation = FormFactory::createForm("Translate");
            float x = 0, y = 0, z = 0;
            auto &properties = t.lookup("properties");
            properties.lookupValue("x", x); properties.lookupValue("y", y); properties.lookupValue("z", z);
            translation->initTranslate(form, Math::Vector3D(x, y, z));
            form = translation;
        }
        if (transformationName == "RotateX") {
            FormPtr rotation = FormFactory::createForm("RotateX");
            float angle = 0;
            auto &properties = t.lookup("properties");
            properties.lookupValue("angle", angle);
            rotation->initRotate(form, angle);
            form = rotation;
        }
        if (transformationName == "RotateY") {
            FormPtr rotation = FormFactory::createForm("RotateY");
            float angle = 0;
            auto &properties = t.lookup("properties");
            properties.lookupValue("angle", angle);
            rotation->initRotate(form, angle);
            form = rotation;
        }
        if (transformationName == "RotateZ") {
            FormPtr rotation = FormFactory::createForm("RotateZ");
            float angle = 0;
            auto &properties = t.lookup("properties");
            properties.lookupValue("angle", angle);
            rotation->initRotate(form, angle);
            form = rotation;
        }
        if (transformationName == "ConstantMedium") {
            FormPtr constantMedium = FormFactory::createForm("ConstantMedium");
            float density = 0, colorR = 0, colorG = 0, colorB = 0;
            auto &properties = t.lookup("properties");
            properties.lookupValue("density", density);
            auto &color = properties.lookup("color");
            color.lookupValue("r", colorR); color.lookupValue("g", colorG); color.lookupValue("b", colorB);
            constantMedium->initConstantMedium(form, density, Math::Color(colorR, colorG, colorB));
            form = constantMedium;
        }
    }
}

FormPtr RayTracer::Parser::getForm(const std::string &name, const libconfig::Setting &form)
{
    FormPtr newForm = nullptr;
    if (name == "spheres") {
        std::string formName = form.lookup("name");
        if (formName == "Sphere") {
            float sphereX = 0, sphereY = 0, sphereZ = 0, sphereRadius = 0;
            int colorR = 0, colorG = 0, colorB = 0;
            form.lookupValue("color.r", colorR);
            form.lookupValue("color.g", colorG);
            form.lookupValue("color.b", colorB);
            form.lookupValue("x", sphereX);
            form.lookupValue("y", sphereY);
            form.lookupValue("z", sphereZ);
            form.lookupValue("radius", sphereRadius);
            newForm = FormFactory::createForm(formName);
            newForm->setCenter(Math::Point3D(sphereX, sphereY, sphereZ));
            newForm->setRadius((double) sphereRadius);
            newForm->setColor(Math::Color(colorR, colorG, colorB));
            if (form.exists("material")) {
                MaterialPtr material = getMaterial(form.lookup("material"));
                newForm->setMaterial(material);
            } else
                newForm->setMaterial(nullptr);
        } else if (formName == "MovingSphere") {
            float sphereX0 = 0, sphereY0 = 0, sphereZ0 = 0, sphereX1 = 0, sphereY1 = 0, sphereZ1 = 0, sphereRadius = 0;
            int colorR = 0, colorG = 0, colorB = 0;
            form.lookupValue("color.r", colorR);
            form.lookupValue("color.g", colorG);
            form.lookupValue("color.b", colorB);
            form.lookupValue("x0", sphereX0);
            form.lookupValue("y0", sphereY0);
            form.lookupValue("z0", sphereZ0);
            form.lookupValue("x1", sphereX1);
            form.lookupValue("y1", sphereY1);
            form.lookupValue("z1", sphereZ1);
            form.lookupValue("radius", sphereRadius);
            newForm = FormFactory::createForm(formName);
            newForm->setCenter0(Math::Point3D(sphereX0, sphereY0, sphereZ0));
            newForm->setCenter1(Math::Point3D(sphereX1, sphereY1, sphereZ1));
            newForm->setTime0(0.0);
            newForm->setTime1(1.0);
            newForm->setRadius((double) sphereRadius);
            newForm->setColor(Math::Color(colorR, colorG, colorB));
            if (form.exists("material")) {
                MaterialPtr material = getMaterial(form.lookup("material"));
                newForm->setMaterial(material);
            } else
                newForm->setMaterial(nullptr);
        }
    } else if (name == "rectangles") {
        std::string formName = form.lookup("name");
        if (formName == "RectangleXY") {
            float x0 = 0, x1 = 0, y0 = 0, y1 = 0, k = 0;
            form.lookupValue("x0", x0); form.lookupValue("x1", x1); form.lookupValue("y0", y0); form.lookupValue("y1", y1); form.lookupValue("k", k);
            newForm = FormFactory::createForm(formName);
            newForm->initRectangle(x0, x1, y0, y1, 0, 0, k);
        } else if (formName == "RectangleXZ") {
            float x0 = 0, x1 = 0, z0 = 0, z1 = 0, k = 0;
            form.lookupValue("x0", x0); form.lookupValue("x1", x1); form.lookupValue("z0", z0); form.lookupValue("z1", z1); form.lookupValue("k", k);
            newForm = FormFactory::createForm(formName);
            newForm->initRectangle(x0, x1, 0, 0, z0, z1, k);
        } else if (formName == "RectangleYZ") {
            float y0 = 0, y1 = 0, z0 = 0, z1 = 0, k = 0;
            form.lookupValue("y0", y0); form.lookupValue("y1", y1); form.lookupValue("z0", z0); form.lookupValue("z1", z1); form.lookupValue("k", k);
            newForm = FormFactory::createForm(formName);
            newForm->initRectangle(0, 0, y0, y1, z0, z1, k);
        }
        if (form.exists("material")) {
            MaterialPtr material = getMaterial(form.lookup("material"));
            newForm->setMaterial(material);
        } else
            newForm->setMaterial(nullptr);
    } else if (name == "boxes") {
        std::string formName = form.lookup("name");
        float point0X = 0, point0Y = 0, point0Z = 0, point1X = 0, point1Y = 0, point1Z = 0;
        auto &point0 = form.lookup("point0");
        auto &point1 = form.lookup("point1");
        point0.lookupValue("x", point0X); point0.lookupValue("y", point0Y); point0.lookupValue("z", point0Z);
        point1.lookupValue("x", point1X); point1.lookupValue("y", point1Y); point1.lookupValue("z", point1Z);
        MaterialPtr material;
        newForm = FormFactory::createForm(formName);
        if (form.exists("material")) {
            material = getMaterial(form.lookup("material"));
            newForm->initBox(Math::Point3D(point0X, point0Y, point0Z), Math::Point3D(point1X, point1Y, point1Z), material);
        } else
            newForm->setMaterial(nullptr);
    } else if (name == "bvh") {
        RayTracer::Forms::FormList forms;
        auto &bvh = form.lookup("primitives");
        for (auto &f : bvh) {
            std::string name = f.getName();
            for (auto &p : bvh.lookup(name)) {
                FormPtr form = getForm(name, p);
                if (form != nullptr) {
                    forms.add(form);
                    form = nullptr;
                }
            }
        }
        auto bvhBox = std::make_shared<RayTracer::Forms::BVHNode>(forms, 0, 1);
        newForm = bvhBox;
    } else if (name == "cylinders") {
        std::string formName = form.lookup("name");
        newForm = FormFactory::createForm(formName);
        float x = 0, y = 0, z = 0, radius = 0, height = 0;
        form.lookupValue("x", x); form.lookupValue("y", y); form.lookupValue("z", z); form.lookupValue("radius", radius); form.lookupValue("height", height);
        newForm->setCenter(Math::Point3D(x, y, z));
        newForm->setRadius(radius);
        newForm->setHeight(height);
        if (form.exists("material")) {
            MaterialPtr material = getMaterial(form.lookup("material"));
            newForm->setMaterial(material);
        } else
            newForm->setMaterial(nullptr);
    } else if (name == "planes") {
        std::string formName = form.lookup("name");
        std::string axis = form.lookup("axis");
        float position = 0;
        form.lookupValue("position", position);
        if (axis == "X") {
            newForm = FormFactory::createForm("RectangleYZ");
            newForm->initRectangle(0, 0, -10000, 10000, -10000, 10000, position);
        } else if (axis == "Y") {
            newForm = FormFactory::createForm("RectangleXZ");
            newForm->initRectangle(-10000, 10000, 0, 0, -10000, 10000, position);
        } else if (axis == "Z") {
            newForm = FormFactory::createForm("RectangleXY");
            newForm->initRectangle(-10000, 10000, -10000, 10000, 0, 0, position);
        }
    }

    if (form.exists("transformations"))
        getTransformations(newForm, form.lookup("transformations"));

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

    auto bvhBox = std::make_shared<RayTracer::Forms::BVHNode>(world, 0, 1);
    world.clear();
    world.add(bvhBox);

    return world;
}
