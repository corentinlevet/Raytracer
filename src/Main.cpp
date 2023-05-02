/*
** EPITECH PROJECT, 2022
** Main.cpp
** File description:
** Main file for the Raytracer project
*/

#include "Main.hpp"

int usage(int status)
{
    std::cout << "USAGE" << std::endl;
    std::cout << "\t./raytracer <SCENE_FILE>" << std::endl << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\t<SCENE_FILE>\tscene configuration" << std::endl;
    return (status);
}

int main(int ac, char **av)
{
    (void)ac; (void)av;

    RayTracer::Camera::Camera cam;
    FormPtr sphere = FormFactory::createForm("Sphere");
    sphere->setRadius(0.25);
    sphere->setCenter(RayTracer::Math::Point3D(0.5, 0.5, 0));
    cam.setOrigin(RayTracer::Math::Point3D(0, 0, -10));
    std::cout << "P3" << std::endl;
    std::cout << "400 400" << std::endl;
    std::cout << "255" << std::endl;
    for (int y = 0; y < 400; y++) {
        for (int x = 0; x < 400; x++) {
            double u = double(x) / 400;
            double v = double(y) / 400;
            RayTracer::Ray ray = cam.ray(u, v);
            if (sphere->hits(ray))
                std::cout << "255 0 0" << std::endl;
            else
                std::cout << "128 192 255" << std::endl;
        }
    }

    return (0);
}
