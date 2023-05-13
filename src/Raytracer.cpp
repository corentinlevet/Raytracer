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

RayTracer::Forms::FormList RayTracer::Raytracer::simpleLight()
{
    auto perlinTexture = TextureFactory::createTexture("Perlin");
    perlinTexture->setScale(4.0);

    auto sphereMaterial = MaterialFactory::createMaterial("Lambertian");
    sphereMaterial->setTexture(perlinTexture);
    sphereMaterial->setAlbedo(RayTracer::Math::Color(0.5, 0.5, 0.5));

    auto sphere1 = FormFactory::createForm("Sphere");
    auto sphere2 = FormFactory::createForm("Sphere");

    sphere1->setCenter(RayTracer::Math::Point3D(0, -1000, 0));
    sphere1->setRadius(1000);
    sphere1->setMaterial(sphereMaterial);

    sphere2->setCenter(RayTracer::Math::Point3D(0, 2, 0));
    sphere2->setRadius(2);
    sphere2->setMaterial(sphereMaterial);

    auto lightTexture = TextureFactory::createTexture("SolidColor");
    lightTexture->setColor(RayTracer::Math::Color(4, 4, 4));

    auto diffuseLight = LightFactory::createLight("Diffuse");
    diffuseLight->setTexture(lightTexture);

    auto rectangle = FormFactory::createForm("RectangleXY");

    rectangle->initRectangle(3, 5, 1, 3, 0, 0, -2);
    rectangle->setMaterial(diffuseLight);

    RayTracer::Forms::FormList world;

    world.add(sphere1);
    world.add(sphere2);

    world.add(rectangle);

    return world;
}

RayTracer::Forms::FormList RayTracer::Raytracer::cornellBox()
{
    auto solidColor1 = TextureFactory::createTexture("SolidColor");
    solidColor1->setColor(RayTracer::Math::Color(0.65, 0.05, 0.05));
    auto red = MaterialFactory::createMaterial("Lambertian");
    red->setTexture(solidColor1);
    auto solidColor2 = TextureFactory::createTexture("SolidColor");
    solidColor2->setColor(RayTracer::Math::Color(0.73, 0.73, 0.73));
    auto white = MaterialFactory::createMaterial("Lambertian");
    white->setTexture(solidColor2);
    auto solidColor3 = TextureFactory::createTexture("SolidColor");
    solidColor3->setColor(RayTracer::Math::Color(0.12, 0.45, 0.15));
    auto green = MaterialFactory::createMaterial("Lambertian");
    green->setTexture(solidColor3);
    auto solidColor4 = TextureFactory::createTexture("SolidColor");
    solidColor4->setColor(RayTracer::Math::Color(15, 15, 15));
    auto light = LightFactory::createLight("Diffuse");
    light->setTexture(solidColor4);

    auto lightRect = FormFactory::createForm("RectangleXZ");
    lightRect->initRectangle(213, 343, 0, 0, 227, 332, 554);
    lightRect->setMaterial(light);

    auto greenRect = FormFactory::createForm("RectangleYZ");
    greenRect->initRectangle(0, 0, 0, 555, 0, 555, 555);
    greenRect->setMaterial(green);

    auto redRect = FormFactory::createForm("RectangleYZ");
    redRect->initRectangle(0, 0, 0, 555, 0, 555, 0);
    redRect->setMaterial(red);

    auto whiteRect1 = FormFactory::createForm("RectangleXZ");
    whiteRect1->initRectangle(0, 555, 0, 0, 0, 555, 0);
    whiteRect1->setMaterial(white);

    auto whiteRect2 = FormFactory::createForm("RectangleXZ");
    whiteRect2->initRectangle(0, 555, 0, 0, 0, 555, 555);
    whiteRect2->setMaterial(white);

    auto whiteRect3 = FormFactory::createForm("RectangleXY");
    whiteRect3->initRectangle(0, 555, 0, 555, 0, 0, 555);
    whiteRect3->setMaterial(white);

    auto box1 = FormFactory::createForm("Box");
    box1->initBox(RayTracer::Math::Point3D(0, 0, 0), RayTracer::Math::Point3D(165, 330, 165), white);
    auto rotate1 = FormFactory::createForm("RotateY");
    rotate1->initRotate(box1, 15);
    auto translate1 = FormFactory::createForm("Translate");
    translate1->initTranslate(rotate1, RayTracer::Math::Vector3D(265, 0, 295));

    auto box2 = FormFactory::createForm("Box");
    box2->initBox(RayTracer::Math::Point3D(0, 0, 0), RayTracer::Math::Point3D(165, 165, 165), white);
    auto rotate2 = FormFactory::createForm("RotateY");
    rotate2->initRotate(box2, -18);
    auto translate2 = FormFactory::createForm("Translate");
    translate2->initTranslate(rotate2, RayTracer::Math::Vector3D(130, 0, 65));

    RayTracer::Forms::FormList world;

    world.add(lightRect);
    world.add(greenRect);
    world.add(redRect);
    world.add(whiteRect1);
    world.add(whiteRect2);
    world.add(whiteRect3);
    world.add(translate1);
    world.add(translate2);

    return world;
}

RayTracer::Forms::FormList RayTracer::Raytracer::cornellSmoke()
{
    auto solidColor1 = TextureFactory::createTexture("SolidColor");
    solidColor1->setColor(RayTracer::Math::Color(0.65, 0.05, 0.05));
    auto red = MaterialFactory::createMaterial("Lambertian");
    red->setTexture(solidColor1);
    auto solidColor2 = TextureFactory::createTexture("SolidColor");
    solidColor2->setColor(RayTracer::Math::Color(0.73, 0.73, 0.73));
    auto white = MaterialFactory::createMaterial("Lambertian");
    white->setTexture(solidColor2);
    auto solidColor3 = TextureFactory::createTexture("SolidColor");
    solidColor3->setColor(RayTracer::Math::Color(0.12, 0.45, 0.15));
    auto green = MaterialFactory::createMaterial("Lambertian");
    green->setTexture(solidColor3);
    auto solidColor4 = TextureFactory::createTexture("SolidColor");
    solidColor4->setColor(RayTracer::Math::Color(7, 7, 7));
    auto light = LightFactory::createLight("Diffuse");
    light->setTexture(solidColor4);

    auto lightRect = FormFactory::createForm("RectangleXZ");
    lightRect->initRectangle(113, 443, 0, 0, 127, 432, 554);
    lightRect->setMaterial(light);

    auto greenRect = FormFactory::createForm("RectangleYZ");
    greenRect->initRectangle(0, 0, 0, 555, 0, 555, 555);
    greenRect->setMaterial(green);

    auto redRect = FormFactory::createForm("RectangleYZ");
    redRect->initRectangle(0, 0, 0, 555, 0, 555, 0);
    redRect->setMaterial(red);

    auto whiteRect1 = FormFactory::createForm("RectangleXZ");
    whiteRect1->initRectangle(0, 555, 0, 0, 0, 555, 0);
    whiteRect1->setMaterial(white);

    auto whiteRect2 = FormFactory::createForm("RectangleXZ");
    whiteRect2->initRectangle(0, 555, 0, 0, 0, 555, 555);
    whiteRect2->setMaterial(white);

    auto whiteRect3 = FormFactory::createForm("RectangleXY");
    whiteRect3->initRectangle(0, 555, 0, 555, 0, 0, 555);
    whiteRect3->setMaterial(white);

    auto box1 = FormFactory::createForm("Box");
    box1->initBox(RayTracer::Math::Point3D(0, 0, 0), RayTracer::Math::Point3D(165, 330, 165), white);
    auto rotate1 = FormFactory::createForm("RotateY");
    rotate1->initRotate(box1, 15);
    auto translate1 = FormFactory::createForm("Translate");
    translate1->initTranslate(rotate1, RayTracer::Math::Vector3D(265, 0, 295));

    auto box2 = FormFactory::createForm("Box");
    box2->initBox(RayTracer::Math::Point3D(0, 0, 0), RayTracer::Math::Point3D(165, 165, 165), white);
    auto rotate2 = FormFactory::createForm("RotateY");
    rotate2->initRotate(box2, -18);
    auto translate2 = FormFactory::createForm("Translate");
    translate2->initTranslate(rotate2, RayTracer::Math::Vector3D(130, 0, 65));

    auto constantMedium1 = FormFactory::createForm("ConstantMedium");
    constantMedium1->initConstantMedium(translate1, 0.01, RayTracer::Math::Color(0, 0, 0));
    auto constantMedium2 = FormFactory::createForm("ConstantMedium");
    constantMedium2->initConstantMedium(translate2, 0.01, RayTracer::Math::Color(1, 1, 1));

    RayTracer::Forms::FormList world;

    world.add(lightRect);
    world.add(greenRect);
    world.add(redRect);
    world.add(whiteRect1);
    world.add(whiteRect2);
    world.add(whiteRect3);
    world.add(constantMedium1);
    world.add(constantMedium2);

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

    const int samplesPerPixel = 25;
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
                pixelColor += ray.rayColor(ray, _background, _world, maxDepth);
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
        _background = RayTracer::Math::Color(0.70, 0.80, 1.00);
        _camera = parser.getCamera(_camera);
        _world = parser.getWorld();
        // switch (0) {
        //     case 1:
        //         _world = randomScene();
        //         break;
        //     default:
        //     case 5:
        //         _background = RayTracer::Math::Color(0.0, 0.0, 0.0);
        //         _world = simpleLight();
        //         break;
        //     case 6:
        //         _background = RayTracer::Math::Color(0.0, 0.0, 0.0);
        //         _world = cornellBox();
        //         break;
        //     case 7:
        //         _background = RayTracer::Math::Color(0.0, 0.0, 0.0);
        //         _world = cornellSmoke();
        //         break;
        //     case 8:
        //         _background = RayTracer::Math::Color(0.0, 0.0, 0.0);
        //         _world = finalScene();
        //         break;
        // }
    } catch (const RayTracer::Parser::hardError &e) {
        throw RayTracer::Raytracer::hardError("Raytracer", "Error while parsing the scene file: " + std::string(e.what()));
    }
}
