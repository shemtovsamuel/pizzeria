/*
** EPITECH PROJECT, 2022
** B-CCP-400-PAR-4-1-theplazza-mayeul.kergall
** File description:
** utils
*/

#include <string>

bool IsNumber(std::string str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (std::isdigit(str[i]) == 0 && (i != 0 && str[i] != '-'))
            throw str.c_str();
    }
    return true;
}

bool IsPositiveNumber(std::string str)
{
    if (IsNumber(str) && atoi(str.c_str()) > 0)
        return true;
    throw "no negativ number plz\n";
}