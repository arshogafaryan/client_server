#ifndef CONNECTION_H
#define CONNECTION_H
#include <iostream>
#include <cstring>
#include <netdb.h>
#include <unistd.h>
#include <string>
using SOCKET = int;

class Connection 
{
public:
    Connection();
    ~Connection();
    void receive();
    std::string get_data();
private:
    SOCKET socket_listen;
    SOCKET client_socket;

    char buf[BUFSIZ];

    struct addrinfo hints;
    struct addrinfo* servinfo;
};

#endif