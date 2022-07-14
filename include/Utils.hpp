/*
** EPITECH PROJECT, 2022
** B-CCP-400-PAR-4-1-theplazza-mayeul.kergall
** File description:
** Utils
*/

#include <string>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>

#include <memory>

#ifndef UTILS_HPP_
#define UTILS_HPP_

bool IsNumber(std::string str);
bool IsPositiveNumber(std::string str);

enum PizzaType
{
    Regina = 1,
    Margarita = 2,
    Americana = 4,
    Fantasia = 8,
};

enum PizzaSize
{
    S = 1,
    M = 2,
    L = 4,
    XL = 8,
    XXL = 16
};

class Order {
public:
    Order() {};
    Order(bool GetType) : Size(S), Type(Regina), GetInfo(GetType) {};
    Order(PizzaSize Size, PizzaType Type) : Size(Size), Type(Type) {};
    Order(std::string type, std::string size);
    ~Order();

    PizzaSize Size;
    PizzaType Type;
    bool GetInfo = false;
    // std::size_t Quantity;
    // std::string Type;
    // std::string Size;
    // std::string Quantity;
};

class ParserOrder {
public:
    ParserOrder() {};
    ~ParserOrder() = default;
    std::vector<std::shared_ptr<Order>> orders;
    void ParseOrder(std::string str);
private:
    std::string CleanSpaceString(std::string str);
    bool CheckStrIsDigit(std::string str);
    bool CheckPizzaType(std::string str);
    bool CheckPizzaSize(std::string str);
    bool CheckPizzaQuantity(std::string str);
    bool CheckAllParams(std::string type, std::string size, std::string quantity);
    int NbOrder(std::string str);
};

#endif /* !UTILS_HPP_ */
