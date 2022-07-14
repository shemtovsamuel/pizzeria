/*
** EPITECH PROJECT, 2022
** B-CCP-400-PAR-4-1-theplazza-mayeul.kergall
** File description:
** Kitchen
*/

#include "Kitchen.hpp"

Kitchen::Kitchen(size_t arg1, int arg2, int arg3) : Client(), _fridge(arg3), _thread_fridge(&Kitchen::RunFridge, this), /*_cooks(5),*/ _thread_cooks(arg2)
{
    // std::cout << "[New Kitchen]" << std::endl;
    this->InitKitchen(arg1, arg2, arg3);
}

Kitchen::Kitchen(socket_t _socket) : Client(_socket)
{
}

Kitchen::~Kitchen()
{
}

void Kitchen::InitKitchen(size_t arg1, int arg2, int arg3)
{
    this->_NbCook = arg2;
    this->_CookkingTime = arg1;
    this->_TimeToReplaceIngredient = arg3;
    // std::cout << "debug 0\n";
    for (int i = 0; i < arg2; i += 1) {
        _thread_cooks[i] = std::thread(&Kitchen::RunCook, this, i);
        _cooks.push_back(std::make_shared<Cook>(arg1));
    }
    // std::cout << "debug 1\n";
}

bool Kitchen::OrderPizza(Order *order)
{
    bool KitchenAccepted = false;

    if (send(this->_Socket, order, sizeof(Order), MSG_NOSIGNAL) == -1)
        throw Exception::ErrorOrder("Error when send one pizza");
    if (recv(this->_Socket, &KitchenAccepted, 1, MSG_NOSIGNAL) == -1)
        throw Exception::ErrorOrder("Error when recv respond from kitchen");
    return KitchenAccepted;
}

void Kitchen::_DisplayInfo()
{
    int NbCook = _NbCook;

    _fridge._Mutex.lock();
    printf("\n---------- Fridge Ingredients ----------\n");
    printf("\t- Doe:\t\t%d\n", (int)_fridge._NbDoe);
    printf("\t- Tomato:\t%d\n", (int)_fridge._NbTomato);
    printf("\t- Gruyere:\t%d\n", (int)_fridge._NbGruyere);
    printf("\t- Ham:\t\t%d\n", (int)_fridge._NbHam);
    printf("\t- Mushrooms:\t%d\n", (int)_fridge._NbMushrooms);
    printf("\t- Steak:\t%d\n", (int)_fridge._NbSteak);
    printf("\t- Eggplant:\t%d\n", (int)_fridge._NbEggplant);
    printf("\t- Goat Cheese:\t%d\n", (int)_fridge._NbGoatCheese);
    printf("\t- Chief Love:\t%d\n\n", (int)_fridge._NbChiefLove);

    printf("---------------- Cooks -----------------\n");
    for (int i = 0; i < NbCook; i += 1) {
        printf("\t- Cook %d:", (i + 1));
        if (_cooks[i]->_is_free)
            printf("\tFree\n");
        else
            printf("\tBusy\n");
    }

    _fridge._Mutex.unlock();
}

void Kitchen::Run()
{
    ConnectToKitchen();
    while (1) {
        try {
            this->Select();
        } catch (Exception::TimeOutSelect &e) {
            size_t i = 0;
            for (const auto& Elem : this->_cooks) {
                Elem.get()->_MutexCook.lock();
                if (Elem.get()->_is_free == true)
                    ++i;
                Elem.get()->_MutexCook.unlock();
            }
            if (i == this->_cooks.size())
                break;
        } catch (Order &order) {
            if (order.GetInfo) {
                this->_DisplayInfo();
                this->_RepondToReseption(true);
                continue;
            }
            this->_list_command.SetOnCue(order);
            // this->_RepondToReseption(true);
        } catch (...) {
            // std::cout << "[Kitchen Stop]" << std::endl;
            break;
        }
    }
    printf("[STOP] Kitchen\n");
}

void Kitchen::RunFridge()
{
    // std::cout << "fridge \n";
    bool check_cook = false;
    std::thread Handleregen(&Kitchen::HandleTime, this);
        std::shared_ptr<Order> order;
        while(1) {
            check_cook = false;
            try {
                order = this->_list_command.GetOnCue();
                switch (order.get()->Type)
                {
                case Regina:
                    _fridge.DoRegina();
                    // std::cout << "regina\n";
                    // this->_list_command_for_cooks.SetOnCue(order.get());
                    break;
                case Margarita:
                    _fridge.DoMargarita();
                    // this->_list_command_for_cooks.SetOnCue(order.get());
                    break;
                case Americana:
                    _fridge.DoAmericana();
                    // this->_list_command_for_cooks.SetOnCue(order.get());
                    break;
                case Fantasia:
                    _fridge.DoFantasia();
                    // this->_list_command_for_cooks.SetOnCue(order.get());
                    break;
                default:
                    break;
                }
                for (size_t i = 0; i < _cooks.size(); i++) {
                    _cooks[i].get()->_MutexCook.lock();
                    if (_cooks[i].get()->_is_free) {
                        _cooks[i].get()->_list.SetOnCue(order.get()->Size, order.get()->Type);
                        _cooks[i].get()->_MutexCook.unlock();
                        check_cook = true;
                        break;
                    }
                    _cooks[i].get()->_MutexCook.unlock();
                }
                if (check_cook == false) {
                    throw Exception::ErrorNotEnoughIngredients("not enought cook\n");
                }
                this->_RepondToReseption(true);
            }  catch (Exception::ErrorNotEnoughIngredients &e) {
                this->_RepondToReseption(false);
            } catch (std::exception &e) {
                    // std::cerr << e.what() << "\n";
            }
        }
}

void Kitchen::RunCook(size_t idx)
{
    // std::cout << "run cook\n";
    std::shared_ptr<Order> order;
        while(1) {
                try {
                    order = this->_cooks[idx].get()->_list.GetOnCue();
                    switch (order.get()->Type)
                    {
                    case Regina:
                        _cooks[idx].get()->DoRegina();
                        break;
                    case Margarita:
                        _cooks[idx].get()->DoMargarita();
                        break;
                    case Americana:
                        _cooks[idx].get()->DoAmericana();
                        break;
                    case Fantasia:
                        _cooks[idx].get()->DoFantasia();
                        break;
                    default:
                        break;
                    }
                }  catch (std::exception &e) {
                }
        }
}

Fridge::Fridge(int TimeRegen)
{
    this->_timeRegen = TimeRegen;
}

Fridge::~Fridge()
{
}

void Kitchen::HandleTime()
{
    while(1) {
        sleep(this->_fridge._timeRegen);
        _fridge._Mutex.lock();
        _fridge.Regeneration();
        _fridge._Mutex.unlock();
    }
}

bool Fridge::CheckMargarita()
{
    if (_NbDoe < 1 || _NbTomato < 1 || _NbGruyere < 1)
        return false;
    return true;
}

bool Fridge::CheckRegina()
{
    if (_NbDoe < 1 || _NbTomato < 1 || _NbGruyere < 1 ||
    _NbHam < 1 || _NbMushrooms < 1)
        return false;
    return true;
}

bool Fridge::CheckAmericana()
{
    if (_NbDoe < 1 || _NbTomato < 1 || _NbGruyere < 1 ||
    _NbSteak < 1)
        return false;
    return true;
}

bool Fridge::CheckFantasia()
{
    if (_NbDoe < 1 || _NbTomato < 1 || _NbEggplant < 1 ||
    _NbGoatCheese < 1 || _NbChiefLove < 1)
        return false;
    return true;
}

void Fridge::Regeneration()
{
    _NbDoe += 1;
    _NbTomato += 1;
    _NbGruyere += 1;
    _NbHam += 1;
    _NbMushrooms += 1;
    _NbSteak += 1;
    _NbEggplant += 1;
    _NbGoatCheese += 1;
    _NbChiefLove += 1;
}

void Fridge::DoRegina()
{
    _Mutex.lock();
    if (CheckRegina()) {
        _NbDoe -= 1;
        _NbTomato -= 1;
        _NbGruyere -= 1;
        _NbHam -= 1;
        _NbMushrooms -= 1;
    } else {
        _Mutex.unlock();
        throw Exception::ErrorNotEnoughIngredients("Error when do Regina Pizza");
    }
    _Mutex.unlock();
}

void Fridge::DoMargarita()
{
    _Mutex.lock();
    if (CheckMargarita()) {
        _NbDoe -= 1;
        _NbTomato -= 1;
        _NbGruyere -= 1;
    } else {
        _Mutex.unlock();
        throw Exception::ErrorNotEnoughIngredients("Error when do Maragarita Pizza");
    }
    _Mutex.unlock();
}

void Fridge::DoAmericana()
{
    _Mutex.lock();
    if (CheckAmericana()) {
        _NbDoe -= 1;
        _NbTomato -= 1;
        _NbGruyere -= 1;
        _NbSteak -= 1;
    } else {
        _Mutex.unlock();
        throw Exception::ErrorNotEnoughIngredients("Error when do Americana Pizza");
    }
    _Mutex.unlock();
}

void Fridge::DoFantasia()
{
    _Mutex.lock();
    if (CheckFantasia()) {
        _NbDoe -= 1;
        _NbTomato -= 1;
        _NbEggplant -= 1;
        _NbGoatCheese -= 1;
        _NbChiefLove -= 1;
    } else {
        _Mutex.unlock();
        throw Exception::ErrorNotEnoughIngredients("Error when do Fantasia Pizza");
    }
    _Mutex.unlock();
}
