/*
** EPITECH PROJECT, 2022
** Raytracer.cpp
** File description:
** Source file for the Raytracer class
*/

#include "Raytracer.hpp"

#include "BVHNode.hpp"
#include "Parser.hpp"
#include "Random.hpp"
#include "Ray.hpp"

#include "FormFactory.hpp"
#include "LightFactory.hpp"
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

RayTracer::Forms::FormList RayTracer::Raytracer::finalScene()
{
    RayTracer::Forms::FormList boxes1;

    auto groundColor = TextureFactory::createTexture("SolidColor");
    groundColor->setColor(RayTracer::Math::Color(0.48, 0.83, 0.53));

    auto ground = MaterialFactory::createMaterial("Lambertian");
    ground->setTexture(groundColor);

    const int boxesPerSide = 20;
    for (int i = 0; i < boxesPerSide; i++) {
        for (int j = 0; j < boxesPerSide; j++) {
            auto w = 100.0;
            auto x0 = -1000.0 + i * w;
            auto z0 = -1000.0 + j * w;
            auto y0 = 0.0;
            auto x1 = x0 + w;
            auto y1 = 100.0 * (randomDouble() + 0.01);
            auto z1 = z0 + w;

            auto box = FormFactory::createForm("Box");
            box->initBox(RayTracer::Math::Point3D(x0, y0, z0), RayTracer::Math::Point3D(x1, y1, z1), ground);

            boxes1.add(box);
        }
    }

    RayTracer::Forms::FormList world;

    world.add(std::make_shared<RayTracer::Forms::BVHNode>(boxes1, 0, 1));

    auto lightColor = TextureFactory::createTexture("SolidColor");
    lightColor->setColor(RayTracer::Math::Color(7, 7, 7));

    auto light = LightFactory::createLight("Diffuse");
    light->setTexture(lightColor);

    auto lightRect = FormFactory::createForm("RectangleXZ");
    lightRect->initRectangle(123, 423, 0, 0, 147, 412, 554);
    lightRect->setMaterial(light);

    world.add(lightRect);

    auto center1 = RayTracer::Math::Point3D(400, 400, 200);
    auto center2 = center1 + RayTracer::Math::Point3D(30, 0, 0);

    auto movingSphereColor = TextureFactory::createTexture("SolidColor");
    movingSphereColor->setColor(RayTracer::Math::Color(0.7, 0.3, 0.1));

    auto movingSphereMaterial = MaterialFactory::createMaterial("Lambertian");
    movingSphereMaterial->setTexture(movingSphereColor);

    auto movingSphere = FormFactory::createForm("MovingSphere");
    movingSphere->setCenter0(center1);
    movingSphere->setCenter1(center2);
    movingSphere->setTime0(0);
    movingSphere->setTime1(1);
    movingSphere->setRadius(50);
    movingSphere->setMaterial(movingSphereMaterial);

    world.add(movingSphere);

    auto dielectric = MaterialFactory::createMaterial("Dielectric");
    dielectric->setRefractionIndex(1.5);

    auto sphere1 = FormFactory::createForm("Sphere");
    sphere1->setCenter(RayTracer::Math::Point3D(260, 150, 45));
    sphere1->setRadius(50);
    sphere1->setMaterial(dielectric);

    world.add(sphere1);

    auto metal = MaterialFactory::createMaterial("Metal");
    metal->setFuzziness(10);
    metal->setAlbedo(RayTracer::Math::Color(0.8, 0.8, 0.9));

    auto sphere2 = FormFactory::createForm("Sphere");
    sphere2->setCenter(RayTracer::Math::Point3D(0, 150, 145));
    sphere2->setRadius(50);
    sphere2->setMaterial(metal);

    world.add(sphere2);

    auto boundary1 = FormFactory::createForm("Sphere");
    boundary1->setCenter(RayTracer::Math::Point3D(360, 150, 145));
    boundary1->setRadius(70);
    boundary1->setMaterial(dielectric);

    world.add(boundary1);

    auto constantMedium1 = FormFactory::createForm("ConstantMedium");
    constantMedium1->initConstantMedium(boundary1, 0.2, RayTracer::Math::Color(0.2, 0.4, 0.9));

    world.add(constantMedium1);

    auto boundary2 = FormFactory::createForm("Sphere");
    boundary2->setCenter(RayTracer::Math::Point3D(0, 0, 0));
    boundary2->setRadius(5000);
    boundary2->setMaterial(dielectric);

    auto constantMedium2 = FormFactory::createForm("ConstantMedium");
    constantMedium2->initConstantMedium(boundary2, 0.0001, RayTracer::Math::Color(1, 1, 1));

    world.add(constantMedium2);

    auto ematTexture = TextureFactory::createTexture("Image");
    ematTexture->setPath("assets/earthmap.jpg");

    auto emat = MaterialFactory::createMaterial("Lambertian");
    emat->setTexture(ematTexture);

    auto sphere3 = FormFactory::createForm("Sphere");
    sphere3->setCenter(RayTracer::Math::Point3D(400, 200, 400));
    sphere3->setRadius(100);
    sphere3->setMaterial(emat);

    world.add(sphere3);

    auto pertext = TextureFactory::createTexture("Perlin");
    pertext->setScale(0.1);

    auto perMaterial = MaterialFactory::createMaterial("Lambertian");
    perMaterial->setTexture(pertext);
    perMaterial->setAlbedo(RayTracer::Math::Color(1, 1, 1));

    auto sphere4 = FormFactory::createForm("Sphere");
    sphere4->setCenter(RayTracer::Math::Point3D(220, 280, 300));
    sphere4->setRadius(80);
    sphere4->setMaterial(perMaterial);

    world.add(sphere4);

    RayTracer::Forms::FormList boxes2;

    auto whiteTexture = TextureFactory::createTexture("SolidColor");
    whiteTexture->setColor(RayTracer::Math::Color(0.73, 0.73, 0.73));

    auto whiteMaterial = MaterialFactory::createMaterial("Lambertian");
    whiteMaterial->setTexture(whiteTexture);

    int ns = 1000;

    for (int j = 0; j < ns; j++) {
        auto whiteSphere = FormFactory::createForm("Sphere");
        whiteSphere->setRadius(10);
        whiteSphere->setMaterial(whiteMaterial);
        whiteSphere->setCenter(RayTracer::Math::Point3D(165 * randomDouble(), 165 * randomDouble(), 165 * randomDouble()));

        boxes2.add(whiteSphere);
    }

    auto bvhBox2 = std::make_shared<RayTracer::Forms::BVHNode>(boxes2, 0, 1);

    auto rotateBox2 = FormFactory::createForm("RotateY");
    rotateBox2->initRotate(bvhBox2, 15);

    auto translateBox2 = FormFactory::createForm("Translate");
    translateBox2->initTranslate(rotateBox2, RayTracer::Math::Vector3D(-100, 270, 395));

    world.add(translateBox2);

    return world;
}

void RayTracer::Raytracer::run()
{
    std::string fileName = _sceneFile.substr(_sceneFile.find_last_of('/') + 1);
    fileName = fileName.substr(0, fileName.find_last_of('.'));
    fileName = "screenshots/" + fileName + ".ppm";

    std::ofstream file(fileName, std::ios::out | std::ios::trunc);

    if (!file.is_open()) {
        std::cerr << "Error: could not open file " << fileName << std::endl;
        exit(84);
    }

    std::tuple resolution = _camera.getResolution();

    const int imageWidth = std::get<0>(resolution);
    const int imageHeight = static_cast<int>(std::get<1>(resolution) / _camera.getAspectRatio());

    _sfml.initWindow(imageWidth, imageHeight);

    const int samplesPerPixel = 200;
    const int maxDepth = 50;

    std::vector<RayTracer::Math::Color> pixelColors(imageWidth);

    file << "P3" << std::endl;
    file << imageWidth << " " << imageHeight << std::endl;
    file << "255" << std::endl;

    for (int y = imageHeight - 1; y >= 0; y--) {
        std::cerr << "\rScanlines remaining: " << y << " " << std::flush;
        for (int x = 0; x < imageWidth; x++) {
            RayTracer::Math::Color pixelColor(0, 0, 0);
            for (int s = 0; s < samplesPerPixel; s++) {
                double u = (x + randomDouble()) / (imageWidth - 1);
                double v = (y + randomDouble()) / (imageHeight - 1);
                RayTracer::Ray ray = _camera.ray(u, v);
                pixelColor += ray.rayColor(ray, _camera.getBackground(), _world, maxDepth);
            }
            pixelColor.writeColor(file, samplesPerPixel);
            pixelColors.push_back(pixelColor);
            if (_sfml.isWindowOpen())
                _sfml.checkEventClose();
        }
        if (_sfml.isWindowOpen())
            _sfml.printPixels(pixelColors, imageWidth, imageHeight - y - 1, samplesPerPixel);
        pixelColors.clear();
    }

    _sfml.waitWindowClose();

    file.close();

    std::cerr << "\nDone." << std::endl;
}

/* Constructor */

RayTracer::Raytracer::Raytracer(const std::string &sceneFile)
{
    try {
        _sceneFile = sceneFile;
        RayTracer::Parser parser(sceneFile);
        _camera = parser.getCamera(_camera);
        _world = parser.getWorld();
        // switch (0) {
        //     case 1:
        //         _world = randomScene();
        //         break;
        //     default:
        //     case 8:
        //         _world = finalScene();
        //         break;
        // }
    } catch (const RayTracer::Parser::hardError &e) {
        throw RayTracer::Raytracer::hardError("Raytracer", "Error while parsing the scene file: " + std::string(e.what()));
    }
}
