/*
** EPITECH PROJECT, 2022
** B-CCP-400-PAR-4-1-theplazza-mayeul.kergall
** File description:
** Socket
*/

#include <unistd.h>
#include <cstdio>
#include <iostream>

#include <signal.h>

#include "server.hpp"

static void managesig(__attribute__((unused)) int signum)
{
}

IPC::Socket::Serveur::Serveur() : _Socket(socket(AF_UNIX, SOCK_STREAM, 0))
{
    struct sigaction sig;

    memset(&sig, 0, sizeof(struct sigaction));
    if (_Socket == -1) {
        std::perror("Socket");
        throw Exception::CreateSocketProblem("");
        return;
    }
    memset(&this->_Serveraddr, 0, sizeof(this->_Serveraddr));
    this->_Serveraddr.sun_family = AF_UNIX;
    strcpy(this->_Serveraddr.sun_path, "/tmp/serveur");
    if (bind(this->_Socket, (struct sockaddr *)&this->_Serveraddr, SUN_LEN(&this->_Serveraddr)) == -1) {
        std::perror("Bind");
        throw Exception::ImposibleToBind("");
        return;
    }
    if (listen(this->_Socket, SOMAXCONN) == -1) {
        std::perror("Listen");
        throw Exception::ImposibleToListen("");
        return;
    }
    FD_ZERO(&this->_Select.foreinitread);
    FD_SET(0, &this->_Select.foreinitread);
    FD_SET(this->_Socket, &this->_Select.foreinitread);
    this->_Select.nbfds = this->_Socket;
    sig.sa_handler = &managesig;
    sig.sa_flags = 0;
    sigaction(SIGINT, &sig, NULL);
}

IPC::Socket::Serveur::~Serveur()
{
    unlink("/tmp/serveur");
    close(this->_Socket);
}

void IPC::Socket::Serveur::_NewConnection(std::vector<std::shared_ptr<Kitchen>>& _Kitchen)
{
    struct sockaddr_in addrclient;
    socklen_t len = sizeof(struct sockaddr_in);
    socket_t clientfd = accept(this->_Socket,
        (struct sockaddr *) &addrclient, &len);

    _Kitchen.push_back(std::make_shared<Kitchen>(clientfd));
    memcpy(&_Kitchen.back().get()->_Clientaddr, &addrclient, len);
    FD_SET(clientfd, &this->_Select.foreinitread);
    this->_Select.nbfds = this->_Socket;
    for (auto elem : _Kitchen) {
        if (elem.get()->_Socket > this->_Select.nbfds)
            this->_Select.nbfds = elem.get()->_Socket;
    }
}

void IPC::Socket::Serveur::Select()
{
    std::vector<std::shared_ptr<Kitchen>>& _Kitchen = _GetKitchen();
    std::string Input;

    this->_Select.current_socketsread = this->_Select.foreinitread;
    errno = 0;
    this->_Select.retselect = select(this->_Select.nbfds + 1,
        &this->_Select.current_socketsread,
        NULL, NULL, NULL);
    if (this->_Select.retselect == -1) {
        perror(NULL);
        throw Exception::SelectSignal("Bad signal");
        return;
    }
    if (FD_ISSET(0, &this->_Select.current_socketsread)) {
        getline(std::cin, Input);
        throw Exception::RetInput(Input);
    } else if (FD_ISSET(this->_Socket, &this->_Select.current_socketsread)) {
        _NewConnection(_Kitchen);
        return;
    }
    for (std::vector<std::shared_ptr<Kitchen>>::iterator elem = _Kitchen.begin(); elem != _Kitchen.end(); ++elem) {
        if (FD_ISSET(elem->get()->_Socket, &this->_Select.current_socketsread)) {
            FD_CLR(elem->get()->_Socket, &this->_Select.foreinitread);
            _Kitchen.erase(elem);
            this->_Select.nbfds = this->_Socket;
            for (auto tmp : _Kitchen) {
                if (tmp.get()->_Socket > this->_Select.nbfds)
                    this->_Select.nbfds = tmp.get()->_Socket;
            }
            break;
        }
    }
    _RemouveKitchen();
}
