/*
** EPITECH PROJECT, 2022
** B-CCP-400-PAR-4-1-theplazza-mayeul.kergall
** File description:
** Cook
*/

#ifndef COOK_HPP_
#define COOK_HPP_

#include <mutex>
#include "Queue.hpp"

class Cook {
    public:
        Cook(int time);
        ~Cook();
        bool _is_free;
        void DoMargarita();
        void DoRegina();
        void DoAmericana();
        void DoFantasia();
        IPC::Queu _list;
        std::mutex _MutexCook;
    protected:
    private:
        int _CookkingTime;
};

#endif /* !COOK_HPP_ */