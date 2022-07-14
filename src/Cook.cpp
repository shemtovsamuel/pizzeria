/*
** EPITECH PROJECT, 2022
** B-CCP-400-PAR-4-1-theplazza-mayeul.kergall
** File description:
** Cook
*/

#include "Cook.hpp"
#include <unistd.h>

Cook::Cook(int time)
{
    _is_free = true;
    _CookkingTime = time;
}

Cook::~Cook()
{
}

void Cook::DoMargarita()
{
    _MutexCook.lock();
    _is_free = false;
    _MutexCook.unlock();
    sleep(_CookkingTime);
    _MutexCook.lock();
    _is_free = true;
    printf("[DONE] The Margarita pizza is finished.\n");
    _MutexCook.unlock();
}

void Cook::DoRegina()
{
    _MutexCook.lock();
    _is_free = false;
    _MutexCook.unlock();
    sleep(_CookkingTime * 2);
    _MutexCook.lock();
    _is_free = true;
    printf("[DONE] The Regina pizza is finished.\n");
    _MutexCook.unlock();
}

void Cook::DoAmericana()
{
    _MutexCook.lock();
    _is_free = false;
    _MutexCook.unlock();
    sleep(_CookkingTime * 2);
    _MutexCook.lock();
    _is_free = true;
    printf("[DONE] The Americana pizza is finished.\n");
    _MutexCook.unlock();
}

void Cook::DoFantasia()
{
    _MutexCook.lock();
    _is_free = false;
    _MutexCook.unlock();
    sleep(_CookkingTime * 4);
    _MutexCook.lock();
    _is_free = true;
    printf("[DONE] The Fantasia pizza is finished.\n");
    _MutexCook.unlock();
}
