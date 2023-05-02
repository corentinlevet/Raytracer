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
    // if (ac == 2 && (std::string(av[1]) == "-h" || std::string(av[1]) == "--help"))
    //     return (usage(0));

    // if (ac != 2)
    //     return (usage(84));

    // try {
    //     RayTracer::Raytracer raytracer(av[1]);
    //     raytracer.run();
    // } catch (const RayTracer::RayTracer::hardError &e) {
    //     std::cerr << e.what() << std::endl;
    //     return (84);
    // }

    RayTracer::Camera::Camera cam;
    FormPtr sphere = FormFactory::createForm("Sphere");
    sphere->setRadius(0.5);
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
                std::cout << "0 0 255" << std::endl;
        }
    }

    return (0);
}
