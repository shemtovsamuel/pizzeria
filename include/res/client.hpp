/*
** EPITECH PROJECT, 2022
** B-CCP-400-PAR-4-1-theplazza-mayeul.kergall
** File description:
** client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <sys/un.h>
#include <sys/socket.h>

#include <vector>
#include <string>
#include <memory>

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/select.h>

#include <queue>
#include <mutex>

#include <unistd.h>

#include <exception>

typedef int socket_t;

namespace IPC {
    namespace Socket {
        typedef struct selectifo_s
        {
            fd_set foreinitread;
            fd_set current_socketsread;
            struct timeval time;
            int retselect;
            int nbfds;
        } selectinfo_t;

        class Client {
            public:
                Client();
                Client(socket_t _socket);
                ~Client() {
                    close(_Socket);
                };
                void Select();
            public:
                void ConnectToKitchen();
            public:
                socket_t _Socket;
                struct sockaddr_un _Clientaddr;
            private:
                const socklen_t _SocketLen = sizeof(struct sockaddr_un);
                selectinfo_t _Select;
        };
    };
};

namespace Exception {
    enum TypeException {
        NO,
        PROBLEM_SOCKET,
        SELECT,
        GETVAR
    };

    /**
     * @brief Class Execution
     * 
     */
    class Exception : public std::exception {
        public:
            Exception(TypeException type, std::string const &message): _type(type), _message(message) {};

            char const *what() const throw() override
            {
                return _message.c_str();
            }

            TypeException const &getType() const
            {
                return _type;
            }

        protected:
        private:

        /**
         * @brief Le type d'erreur
         * 
         */
        TypeException _type;

        /**
         * @brief Le message a afficher
         * 
         */
        std::string _message;
    };
    #define DEFF_EXEPTION(name, typerror) \
    class name : public Exception { \
        public: \
            name(std::string const &message) : Exception(typerror, message) {} \
    }
    DEFF_EXEPTION(CreateSocketProblem, PROBLEM_SOCKET);
    DEFF_EXEPTION(ImposibleToConnect, PROBLEM_SOCKET);
    DEFF_EXEPTION(ImposibleToBind, PROBLEM_SOCKET);
    DEFF_EXEPTION(ImposibleToListen, PROBLEM_SOCKET);
    DEFF_EXEPTION(TimeOutSelect, SELECT);
    DEFF_EXEPTION(RetInput, GETVAR);
    DEFF_EXEPTION(SelectSignal, PROBLEM_SOCKET);
    DEFF_EXEPTION(RongInput, GETVAR);
    DEFF_EXEPTION(ErrorOrder, PROBLEM_SOCKET);
    DEFF_EXEPTION(ErrorNotEnoughIngredients, GETVAR);
}

#endif /* !CLIENT_HPP_ */
