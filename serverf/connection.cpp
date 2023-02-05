#include "connection.h"

Connection::Connection()
{
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    int optval = 1;
    int gai = getaddrinfo(NULL, "1234", &hints, &servinfo);
    if (gai != 0)
    {
        std::cout << "getaddrinfo: " << gai_strerror(gai) << std::endl;
        exit(1);
    }
    socket_listen = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
    if (socket_listen == -1) 
    {
        perror("socket");
        exit(1);
    }
    if (setsockopt(socket_listen, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int)) == -1) 
    {
        perror("setsockopt");
        exit(1);
    }
    if (bind(socket_listen, servinfo->ai_addr, servinfo->ai_addrlen) == -1) 
    {
        std::cout << "bind: " << strerror(errno) << std::endl;
        exit(1);
    }
    if (listen(socket_listen, 5) != 0) 
    {
        perror("listen");
        exit(1);
    }
    if ((client_socket = accept(socket_listen, NULL, NULL)) == -1) 
    {
        std::cout << "accept: " << strerror(errno) <<std::endl;
        exit(1);
    }
}

void Connection::receive() 
{
    memset(buf, 0, BUFSIZ);
    int rcv = recv(client_socket, buf, BUFSIZ, 0);
    if (rcv == 0) 
    {
        std::cout << "Client closed connection\n";
        exit(1);
    } 
    else if (rcv == -1) 
    {
        perror("recv");
        exit(1);
    }
}

std::string Connection::get_data() 
{
    return std::string(buf);
}

Connection::~Connection() 
{
    close(socket_listen);
    freeaddrinfo(servinfo);
}
