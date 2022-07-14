/*
** EPITECH PROJECT, 2022
** B-CCP-400-PAR-4-1-theplazza-mayeul.kergall
** File description:
** Reception
*/

#ifndef RECEPTION_HPP_
#define RECEPTION_HPP_

#include "server.hpp"
#include "Utils.hpp"
#include "Kitchen.hpp"

class Reception : public IPC::Socket::Serveur {
    public:
    Reception(float CookingTime, int NbCooks, unsigned int TimeReplace);
    ~Reception();
    private:
        void _GetStatus();
        void _CreateKitchen();
        void _NewOrder(std::vector<std::shared_ptr<Order>>& orders);
    public:
        void Run();
    protected:
        std::vector<std::shared_ptr<Kitchen>>& _GetKitchen() override;
        void _AddKitchen() override;
        void _RemouveKitchen() override;
    private:
        std::vector<std::shared_ptr<Kitchen>> _Kitchen;
        size_t _NbKitchen = 0;
        std::string _Inputs;
    private:
        const float _CookingTime;
        const int _NbCooks;
        const unsigned int _TimeReplace;
};

#endif /* !RECEPTION_HPP_ */
