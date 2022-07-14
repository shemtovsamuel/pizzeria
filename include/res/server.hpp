/*
** EPITECH PROJECT, 2022
** B-CCP-400-PAR-4-1-theplazza-mayeul.kergall
** File description:
** server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include "client.hpp"
#include "Kitchen.hpp"

namespace IPC {
    namespace Socket {
        class Serveur {
            public:
                Serveur();
                ~Serveur();
                void Select();
            private:
            virtual void _AddKitchen() = 0;
            virtual void _RemouveKitchen() = 0;
            virtual std::vector<std::shared_ptr<Kitchen>>& _GetKitchen() = 0;
                void _NewConnection(std::vector<std::shared_ptr<Kitchen>>& _Kitchen);
            private:
                socket_t _Socket;
                struct sockaddr_un _Serveraddr;
                selectinfo_t _Select;
        };
    };
};

#endif /* !SERVER_HPP_ */
