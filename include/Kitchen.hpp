/*
** EPITECH PROJECT, 2022
** B-CCP-400-PAR-4-1-theplazza-mayeul.kergall
** File description:
** Kitchen
*/

#ifndef KITCHEN_HPP_
#define KITCHEN_HPP_

#include "client.hpp"
#include "Utils.hpp"
#include "Cook.hpp"
#include<thread>
#include <mutex>
#include <memory>

class Fridge {
    public:
        Fridge() {};
        Fridge(int TimeRegen);
        ~Fridge();
        void DoMargarita();
        void DoRegina();
        void DoAmericana();
        void DoFantasia();
        size_t _NbDoe = 5;
        size_t _NbTomato = 5;
        size_t _NbGruyere = 5;
        size_t _NbHam = 5;
        size_t _NbMushrooms = 5;
        size_t _NbSteak = 5;
        size_t _NbEggplant = 5;
        size_t _NbGoatCheese = 5;
        size_t _NbChiefLove = 5;
        size_t _TimeRegen;
        std::mutex _Mutex;
        void Regeneration();
        int _timeRegen;
    private:
        bool CheckMargarita();
        bool CheckRegina();
        bool CheckAmericana();
        bool CheckFantasia();
};

class Kitchen : public IPC::Socket::Client {
    public:
        Kitchen(size_t arg1, int arg2, int arg3);
        Kitchen(socket_t _socket);
        ~Kitchen();
        void InitKitchen(size_t arg1, int arg2, int arg3);
        void Run();
        bool OrderPizza(Order *order);
        void RunFridge();
    private:
        void _RepondToReseption(bool order) {
            send(this->_Socket, &order, 1, 0);
        }
    private:
        void HandleTime();
        void _DisplayInfo();
        size_t _NbCook;
        int _CookkingTime;
        int _TimeToReplaceIngredient;
        socklen_t _SocketLen = sizeof(struct sockaddr_un);
        Fridge _fridge;
        std::thread _thread_fridge;
        std::vector<std::shared_ptr<Cook>> _cooks;
        std::vector<std::thread> _thread_cooks;
        // std::unique_ptr<Fridge> _fridge;
        IPC::Queu _list_command;
        IPC::Queu _list_command_for_cooks;
        std::mutex _MutexCook;
        void RunCook(size_t idx);
};

#endif /* !KITCHEN_HPP_ */


/*
    std::function
    std::forward
    std::pair
    std::array => instead of char str[]
    std::variant
*/