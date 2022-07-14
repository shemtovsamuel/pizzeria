/*
** EPITECH PROJECT, 2022
** B-CCP-400-PAR-4-1-theplazza-mayeul.kergall
** File description:
** Plazza
*/

#include <iostream>
#include "Utils.hpp"

#ifndef PLAZZA_HPP_
#define PLAZZA_HPP_

class Plazza {
    public:
        Plazza(char const *argv[]);
        ~Plazza();
        void Run();
    protected:
    private:
        void SetParams(char const *argv[]);
        float _cooking_time;
        int _nb_cooks;
        int _time_replace;
};

#endif /* !PLAZZA_HPP_ */