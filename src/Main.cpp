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

    std::unique_ptr<Raytracer::Forms::IForm> cube = Raytracer::Forms::FormFactory::createForm("Cube");
    std::unique_ptr<Raytracer::Forms::IForm> sphere = Raytracer::Forms::FormFactory::createForm("Sphere");

    std::cout << cube->getType() << std::endl;
    std::cout << sphere->getType() << std::endl;

    std::cout << "Ça fonctionne sa mère la pute !!!" << std::endl;

    return (0);
}
