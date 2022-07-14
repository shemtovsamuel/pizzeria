/*
** EPITECH PROJECT, 2022
** B-CCP-400-PAR-4-1-theplazza-mayeul.kergall
** File description:
** main
*/

#include "Plazza.hpp"
#include "Utils.hpp"

int main(int argc, char const *argv[])
{
    if (argc != 4)
        return 84;
    try {
        Plazza tst(argv);
        tst.Run();
    } catch(const char* msg) {
        return 84;
    }
    return 0;
}
