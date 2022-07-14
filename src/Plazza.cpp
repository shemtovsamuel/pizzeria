/*
** EPITECH PROJECT, 2022
** B-CCP-400-PAR-4-1-theplazza-mayeul.kergall
** File description:
** Plazza
*/

#include "Plazza.hpp"
#include "Reception.hpp"

Plazza::Plazza(char const *argv[])
{
    SetParams(argv);
}

Plazza::~Plazza()
{
}

void Plazza::SetParams(char const *argv[])
{
    try {
        IsPositiveNumber(argv[1]) ? _cooking_time = atoi(argv[1]) : _cooking_time = 0;
        IsPositiveNumber(argv[2]) ? _nb_cooks = atoi(argv[2]) : _cooking_time = 0;
        IsPositiveNumber(argv[3]) ? _time_replace = atoi(argv[3]) : _cooking_time = 0;
    } catch(const char *msg) {
        throw " bad arg -> not a number\n";
    }
}

void Plazza::Run()
{
    try {
        Reception r(_cooking_time, _nb_cooks, _time_replace);
        r.Run();
    } catch (...) {
        exit(84);
    }
}