/*
** EPITECH PROJECT, 2022
** B-CCP-400-PAR-4-1-theplazza-mayeul.kergall
** File description:
** Pizza
*/

#include "Pizza.hpp"

Pizza::Pizza::Pizza(int multiplier) : _multiplier(multiplier)
{
    this->_ingredients.push_back(Doe);
    this->_ingredients.push_back(Tomato);
}

Pizza::Pizza::~Pizza()
{
}

Pizza::Margarita::Margarita(int multiplier) : Pizza(multiplier)
{
    this->_ingredients.push_back(Gruyere);
}

Pizza::Regina::Regina(int multiplier) : Margarita(multiplier)
{
    this->_ingredients.push_back(Ham);
    this->_ingredients.push_back(Mushrooms);
    _multiplier *= 2;
}

Pizza::Americana::Americana(int multiplier) : Margarita(multiplier)
{
    this->_ingredients.push_back(Steaks);
    _multiplier *= 2;
}

Pizza::Fantasia::Fantasia(int multiplier) : Pizza(multiplier)
{
    this->_ingredients.push_back(Eggplant);
    this->_ingredients.push_back(GoatCheese);
    this->_ingredients.push_back(ChiefLove);
    _multiplier *= 4;
}