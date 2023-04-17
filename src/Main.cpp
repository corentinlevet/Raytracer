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
    if (ac == 2 && (std::string(av[1]) == "-h" || std::string(av[1]) == "--help"))
        return (usage(0));

    if (ac != 2)
        return (usage(84));

    try {
        Raytracer::Raytracer raytracer(av[1]);
        raytracer.run();
    } catch (const Raytracer::Raytracer::hardError &e) {
        std::cerr << e.what() << std::endl;
        return (84);
    }

    return (0);
}
