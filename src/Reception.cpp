/*
** EPITECH PROJECT, 2022
** B-CCP-400-PAR-4-1-theplazza-mayeul.kergall
** File description:
** Reception
*/

#include <cstdlib>
#include <iostream>

#include "Reception.hpp"

Reception::Reception(float CookingTime, int NbCooks, unsigned int TimeReplace) : _CookingTime(CookingTime),  _NbCooks(NbCooks), _TimeReplace(TimeReplace)
{

}

Reception::~Reception()
{
}

std::vector<std::shared_ptr<Kitchen>>& Reception::_GetKitchen()
{
    return this->_Kitchen;
}

void Reception::_CreateKitchen()
{
    pid_t pid = fork();

    if (pid == 0) {
        Kitchen me(this->_CookingTime, this->_NbCooks, this->_TimeReplace);
        me.Run();
        exit(0);
    }
    this->_NbKitchen += 1;
}

void Reception::_AddKitchen()
{
    this->_NbKitchen++;
}

void Reception::_RemouveKitchen()
{
    this->_NbKitchen--;
}

void Reception::_NewOrder(std::vector<std::shared_ptr<Order>>& orders)
{
    neworder:
    if (this->_Kitchen.size() != _NbKitchen || orders.empty())
        return;
    if (this->_Kitchen.size() == 0) {
        _CreateKitchen();
        return;
    }
    for (auto k = this->_Kitchen.begin();1;) {
        if (orders.empty())
            break;
        auto fistPizza = orders.front();
        try {
            bool retorder = k->get()->OrderPizza(fistPizza.get());
            if (retorder == true) {
                orders.erase(orders.begin());
                goto neworder;
                return;
            } else {
                ++k;
                if (k == this->_Kitchen.end()) {
                    _CreateKitchen();
                    break;
                }
            }
        } catch (...) {
            break;
        }
    }
}

void Reception::_GetStatus()
{
    std::shared_ptr<Order> oder = std::make_shared<Order>(true);

    printf("-------------- %ld Kitchens --------------\n", this->_Kitchen.size());
    for (auto k : this->_Kitchen) {
        try {
            k.get()->OrderPizza(oder.get());
        } catch (...) {
            continue;
        }
    }
}

void Reception::Run()
{
    ParserOrder pather;
    std::string line("status");

    while (1) {
        try {
            Select();
        } catch (Exception::SelectSignal &e) {
            return;
        } catch (Exception::RetInput &e) {
            if (e.what() == line) {
                _GetStatus();
                continue;
            }
            try {
                pather.ParseOrder(e.what());
            } catch (Exception::RongInput &e) {
                std::cerr << e.what() << std::endl;
                continue;
            }
        }
        _NewOrder(pather.orders);
    }
}

// regina XXL x2; fantasia M x3; margarita S x1