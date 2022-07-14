/*
** EPITECH PROJECT, 2021
** B-CCP-400-PAR-4-1-theplazza-mayeul.kergall
** File description:
** parser.cpp
*/

#include "Plazza.hpp"
#include "Utils.hpp"
#include "client.hpp"

Order::Order(std::string type, std::string size)
{
    if (type == "regina")
        this->Type = Regina;
    else if (type == "margarita")
        this->Type = Margarita;
    else if (type == "americana")
        this->Type = Americana;
    else
        this->Type = Fantasia;
    if (size == "S")
        this->Size = S;
    else if (size == "M")
        this->Size = M;
    else if (size == "L")
        this->Size = L;
    else if (size == "XL")
        this->Size = XL;
    else
        this->Size = XXL;
}

Order::~Order()
{
}

bool ParserOrder::CheckStrIsDigit(std::string str)
{
    int len = str.length();

    for (int i = 0; i < len; i++) {
        if (!isdigit(str.at(i)))
            return false;
    }
    return true;
}

bool ParserOrder::CheckPizzaType(std::string str)
{
    int len = str.length();

    for (int i = 0; i < len; ++i) {
        str[i] = tolower((unsigned char)str[i]);
    }
    if (str == "regina" || str == "margarita" || str == "americana" || str == "fantasia")
        return true;
    return false;
}

bool ParserOrder::CheckPizzaSize(std::string str)
{
    int len = str.length();

    for (int i = 0; i < len; ++i)
        str[i] = toupper((unsigned char)str[i]);
    if (str == "S" || str == "M" || str == "L" || str == "XL" || str == "XXL")
        return true;
    return false;
}

bool ParserOrder::CheckPizzaQuantity(std::string str)
{
    std::string temp = str;
    std::string newStr = temp.erase(0,1);

    if ((str.at(0) == 'x' || str.at(0) == 'X') && CheckStrIsDigit(newStr) == true)
        return true;
    return false;
}

bool ParserOrder::CheckAllParams(std::string type, std::string size, std::string quantity)
{
    if (CheckPizzaType(type) == true && CheckPizzaSize(size) == true && CheckPizzaQuantity(quantity) == true)
        return true;
    return false;
}

int ParserOrder::NbOrder(std::string str)
{
    int i = 0;
    int order = 1;

    while (str[i] != '\0') {
        if (str[i] == ';')
            order++;
        i++;
    }
    return order;
}

std::string ParserOrder::CleanSpaceString(std::string str)
{
    int len = str.length();

    for (int i = 0; i < len -1; i++) {
        if ((str[i] == ' ' && str[i + 1] == ' ') ||
            (str[i] == ' ' && str[i + 1] == ';') ||
            (str[i] == ' ' && str[i + 1] == '\0') ||
            (i == 0 && str[i] == ' ')) {
            str.erase(i, 1);
            i--;
        }
    }
    return str;
}

void ParserOrder::ParseOrder(std::string str)
{
    std::string type;
    std::string size;
    std::string quantity;
    std::string newStr = str + ";";
    newStr = CleanSpaceString(newStr);
    int nb_order = NbOrder(newStr);

    this->orders.clear();
    for (int i = 1; i < nb_order; i++) {
        type = newStr.substr(0, newStr.find(' '));
        newStr = newStr.substr(newStr.find(' ') + 1);

        size = newStr.substr(0, newStr.find(' '));
        newStr = newStr.substr(newStr.find(' ') + 1);

        quantity = newStr.substr(0, newStr.find(';'));
        newStr = newStr.substr(newStr.find(';') + 1);

        if (CheckAllParams(type, size, quantity) == false) {
            this->orders.clear();
            throw  Exception::RongInput("Invalid input");
        }
        std::size_t Q = atoi(quantity.erase(0, 1).c_str());

        printf("[ORDER] %s times a %s in size %s\n", quantity.c_str(), type.c_str(), size.c_str());

        for (size_t a = 0; a != Q; ++a) {
            this->orders.push_back(std::make_shared<Order>(type, size));
        }
        newStr.erase(0, 1);
    }
}

// regina XXL x2; fantasia M x3; margarita S x1