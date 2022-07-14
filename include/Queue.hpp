/*
** EPITECH PROJECT, 2021
** B-CCP-400-PAR-4-1-theplazza-mayeul.kergall
** File description:
** Queue.hpp
*/

#include <memory>
#include <queue>
#include "Utils.hpp"
#include "client.hpp"


namespace IPC {
    class Queu {
        public:
            Queu() {};
            ~Queu() = default;
        private:
            std::mutex _Mutex;
            std::queue<std::shared_ptr<Order>> _Queu;
        public:
            void SetOnCue(Order order) {
                _Mutex.lock();
                _Queu.push(std::make_shared<Order>(order));
                _Mutex.unlock();
            }
            void SetOnCue(PizzaSize Size, PizzaType Type) {
                _Mutex.lock();
                _Queu.push(std::make_shared<Order>(Size, Type));
                _Mutex.unlock();
            }
            std::shared_ptr<Order> GetOnCue() {
                _Mutex.lock();
                if (_Queu.size() == 0) {
                    _Mutex.unlock();
                    throw Exception::ErrorOrder("Queue is empty");
                }
                std::shared_ptr<Order> oder = _Queu.front();
                _Queu.pop();
                _Mutex.unlock();
                return oder;
            }
    };
}