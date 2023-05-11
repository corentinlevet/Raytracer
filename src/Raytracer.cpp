/*
** EPITECH PROJECT, 2022
** Raytracer.cpp
** File description:
** Source file for the Raytracer class
*/

#include "Raytracer.hpp"

#include "Parser.hpp"
#include "Random.hpp"
#include "Ray.hpp"

#include "FormFactory.hpp"
#include "MaterialFactory.hpp"
#include "TextureFactory.hpp"

/* Public methods */

RayTracer::Forms::FormList RayTracer::Raytracer::randomScene()
{
    RayTracer::Forms::FormList world;

    auto checker = TextureFactory::createTexture("Checker");
    auto solidcolor1 = TextureFactory::createTexture("SolidColor");
    solidcolor1->setColor(RayTracer::Math::Color(0.0, 0.0, 0.0));
    auto solidcolor2 = TextureFactory::createTexture("SolidColor");
    solidcolor2->setColor(RayTracer::Math::Color(0.9, 0.9, 0.9));
    checker->setTextureOdd(solidcolor1);
    checker->setTextureEven(solidcolor2);

    auto groundMaterial = MaterialFactory::createMaterial("Lambertian");
    groundMaterial->setTexture(checker);
    groundMaterial->setAlbedo(RayTracer::Math::Color(0.5, 0.5, 0.5));

    auto sphere = FormFactory::createForm("Sphere");
    sphere->setCenter(RayTracer::Math::Point3D(0, -1000, 0));
    sphere->setRadius(1000);
    sphere->setMaterial(groundMaterial);

    world.add(sphere);

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto chooseMat = randomDouble();
            auto center = RayTracer::Math::Point3D(a + 0.9 * randomDouble(), 0.2, b + 0.9 * randomDouble());

            if ((center - RayTracer::Math::Point3D(4, 0.2, 0)).length() > 0.9) {
                MaterialPtr sphereMaterial;
                FormPtr sphere;

                if (chooseMat < 0.8) {
                    // Diffuse

                    auto center2 = center + RayTracer::Math::Point3D(0, randomDouble(0, 0.5), 0);

                    sphere = FormFactory::createForm("MovingSphere");
                    sphere->setCenter0(center);
                    sphere->setCenter1(center2);
                    sphere->setTime0(0.0);
                    sphere->setTime1(1.0);
                    sphere->setRadius(0.2);

                    auto albedo = RayTracer::Math::Color(randomDouble(), randomDouble(), randomDouble()) * RayTracer::Math::Color(randomDouble(), randomDouble(), randomDouble());
                    sphereMaterial = MaterialFactory::createMaterial("Lambertian");
                    sphereMaterial->setAlbedo(albedo);
                    sphereMaterial->setTexture(nullptr);
                } else if (chooseMat < 0.95) {
                    // Metal

                    sphere = FormFactory::createForm("Sphere");
                    sphere->setCenter(center);
                    sphere->setRadius(0.2);

                    auto albedo = RayTracer::Math::Color(randomDouble(0.5, 1), randomDouble(0.5, 1), randomDouble(0.5, 1));
                    auto fuzziness = randomDouble(0, 0.5);
                    sphereMaterial = MaterialFactory::createMaterial("Metal");
                    sphereMaterial->setAlbedo(albedo);
                    sphereMaterial->setFuzziness(fuzziness);
                } else {
                    // Glass

                    sphere = FormFactory::createForm("Sphere");
                    sphere->setCenter(center);
                    sphere->setRadius(0.2);

                    sphereMaterial = MaterialFactory::createMaterial("Dielectric");
                    sphereMaterial->setRefractionIndex(1.5);
                }

                sphere->setMaterial(sphereMaterial);

                world.add(sphere);
            }
        }
    }

    auto dielectric = MaterialFactory::createMaterial("Dielectric");
    dielectric->setRefractionIndex(1.5);

    auto sphere1 = FormFactory::createForm("Sphere");
    sphere1->setCenter(RayTracer::Math::Point3D(0, 1, 0));
    sphere1->setRadius(1.0);
    sphere1->setMaterial(dielectric);

    world.add(sphere1);

    auto lambertian = MaterialFactory::createMaterial("Lambertian");
    lambertian->setAlbedo(RayTracer::Math::Color(0.4, 0.2, 0.1));
    lambertian->setTexture(nullptr);

    auto sphere2 = FormFactory::createForm("Sphere");
    sphere2->setCenter(RayTracer::Math::Point3D(-4, 1, 0));
    sphere2->setRadius(1.0);
    sphere2->setMaterial(lambertian);

    world.add(sphere2);

    auto metal = MaterialFactory::createMaterial("Metal");
    metal->setAlbedo(RayTracer::Math::Color(0.7, 0.6, 0.5));
    metal->setFuzziness(0.0);

    auto sphere3 = FormFactory::createForm("Sphere");
    sphere3->setCenter(RayTracer::Math::Point3D(4, 1, 0));
    sphere3->setRadius(1.0);
    sphere3->setMaterial(metal);

    world.add(sphere3);

    return world;
}

RayTracer::Forms::FormList RayTracer::Raytracer::twoSpheres()
{
    auto checker = TextureFactory::createTexture("Checker");
    auto solidcolor1 = TextureFactory::createTexture("SolidColor");
    solidcolor1->setColor(RayTracer::Math::Color(0.0, 0.0, 0.0));
    auto solidcolor2 = TextureFactory::createTexture("SolidColor");
    solidcolor2->setColor(RayTracer::Math::Color(0.9, 0.9, 0.9));
    checker->setTextureOdd(solidcolor1);
    checker->setTextureEven(solidcolor2);

    auto sphereMaterial = MaterialFactory::createMaterial("Lambertian");
    sphereMaterial->setTexture(checker);
    sphereMaterial->setAlbedo(RayTracer::Math::Color(0.5, 0.5, 0.5));

    auto sphere1 = FormFactory::createForm("Sphere");
    sphere1->setCenter(RayTracer::Math::Point3D(0, -10, 0));
    sphere1->setRadius(10);
    sphere1->setMaterial(sphereMaterial);

    auto sphere2 = FormFactory::createForm("Sphere");
    sphere2->setCenter(RayTracer::Math::Point3D(0, 10, 0));
    sphere2->setRadius(10);
    sphere2->setMaterial(sphereMaterial);

    RayTracer::Forms::FormList world;
    world.add(sphere1);
    world.add(sphere2);

    return world;
}

RayTracer::Forms::FormList RayTracer::Raytracer::twoPerlinSpheres()
{
    auto perlin = TextureFactory::createTexture("Perlin");
    perlin->setScale(4.0);

    auto sphereMaterial = MaterialFactory::createMaterial("Lambertian");
    sphereMaterial->setTexture(perlin);
    sphereMaterial->setAlbedo(RayTracer::Math::Color(0.5, 0.5, 0.5));

    auto sphere1 = FormFactory::createForm("Sphere");
    sphere1->setCenter(RayTracer::Math::Point3D(0, -1000, 0));
    sphere1->setRadius(1000);
    sphere1->setMaterial(sphereMaterial);

    auto sphere2 = FormFactory::createForm("Sphere");
    sphere2->setCenter(RayTracer::Math::Point3D(0, 2, 0));
    sphere2->setRadius(2);
    sphere2->setMaterial(sphereMaterial);

    RayTracer::Forms::FormList world;
    world.add(sphere1);
    world.add(sphere2);

    return world;
}

RayTracer::Forms::FormList RayTracer::Raytracer::earth()
{
    auto earthTexture = TextureFactory::createTexture("Image");
    earthTexture->setPath("assets/earthmap.jpg");

    auto earthSurface = MaterialFactory::createMaterial("Lambertian");
    earthSurface->setTexture(earthTexture);

    auto globe = FormFactory::createForm("Sphere");
    globe->setCenter(RayTracer::Math::Point3D(0, 0, 0));
    globe->setRadius(2);
    globe->setMaterial(earthSurface);

    RayTracer::Forms::FormList world;
    world.add(globe);

    return world;
}

void RayTracer::Raytracer::run()
{
    std::cout << "P3" << std::endl;
    std::tuple resolution = _camera.getResolution();

    const int imageWidth = std::get<0>(resolution);
    const int imageHeight = static_cast<int>(std::get<1>(resolution) / _camera.getAspectRatio());

    _sfml.initWindow(imageWidth, imageHeight);

    const int samplesPerPixel = 100;
    const int maxDepth = 50;

    std::cout << imageWidth << " " << imageHeight << std::endl;
    std::cout << "255" << std::endl;

    std::vector<RayTracer::Math::Color> pixelColors(imageWidth);

    for (int y = imageHeight - 1; y >= 0; y--) {
        std::cerr << "\rScanlines remaining: " << y << " " << std::flush;
        for (int x = 0; x < imageWidth; x++) {
            RayTracer::Math::Color pixelColor(0, 0, 0);
            for (int s = 0; s < samplesPerPixel; s++) {
                double u = (x + randomDouble()) / (imageWidth - 1);
                double v = (y + randomDouble()) / (imageHeight - 1);
                RayTracer::Ray ray = _camera.ray(u, v);
                pixelColor += ray.rayColor(ray, _world, maxDepth);
            }
            pixelColor.writeColor(std::cout, samplesPerPixel);
            pixelColors.push_back(pixelColor);
            if (_sfml.isWindowOpen())
                _sfml.checkEventClose();
        }
        if (_sfml.isWindowOpen())
            _sfml.printPixels(pixelColors, imageWidth, imageHeight - y - 1, samplesPerPixel);
        pixelColors.clear();
    }

    _sfml.waitWindowClose();

    std::cerr << "\nDone." << std::endl;
}

/* Constructor */

RayTracer::Raytracer::Raytracer(const std::string &sceneFile)
{
    try {
        RayTracer::Parser parser(sceneFile);
        _camera = parser.getCamera(_camera);
        // _world = parser.getWorld();
        switch (0) {
            case 1:
                _world = randomScene();
                break;
            case 2:
                _world = twoSpheres();
                break;
            case 3:
                _world = twoPerlinSpheres();
                break;
            default:
            case 4:
                _world = earth();
                break;
        }
    } catch (...) {
        throw RayTracer::Raytracer::hardError("Raytracer", "Error while parsing the scene file");
    }
}
