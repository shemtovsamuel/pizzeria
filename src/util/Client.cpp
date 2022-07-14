/*
** EPITECH PROJECT, 2022
** B-CCP-400-PAR-4-1-theplazza-mayeul.kergall
** File description:
** Client
*/

#include "client.hpp"
#include "Utils.hpp"

IPC::Socket::Client::Client() : _Socket(socket(AF_UNIX, SOCK_STREAM, 0))
{
    if (this->_Socket == -1)
        throw Exception::CreateSocketProblem("Can't Create Socket");
    FD_ZERO(&this->_Select.foreinitread);
    FD_SET(this->_Socket, &this->_Select.foreinitread);
    this->_Select.nbfds = this->_Socket;
}

IPC::Socket::Client::Client(socket_t _socket) : _Socket(_socket)
{
}

void IPC::Socket::Client::ConnectToKitchen()
{
    this->_Clientaddr.sun_family = AF_UNIX;
    strcpy(this->_Clientaddr.sun_path, "/tmp/serveur");
    if (connect(this->_Socket, (const struct sockaddr *) &this->_Clientaddr, this->_SocketLen) == -1) {
        perror(NULL);
        throw Exception::ImposibleToConnect("Can't connect");
    }
}

void IPC::Socket::Client::Select()
{
    Order order;

    this->_Select.time.tv_sec = 5;
    this->_Select.time.tv_usec = 0;
    this->_Select.current_socketsread = this->_Select.foreinitread;
    this->_Select.retselect = select(this->_Select.nbfds + 1, &this->_Select.current_socketsread, NULL, NULL, &this->_Select.time);
    if (this->_Select.retselect == -1) {
        throw Exception::ImposibleToConnect("");
    } else if (this->_Select.retselect == 0) {
        throw Exception::TimeOutSelect("");
    } else {
        read(this->_Socket, &order, sizeof(Order));
        throw order;
    }
}
