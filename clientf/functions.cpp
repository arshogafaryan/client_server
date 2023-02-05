#include "functions.h"

bool check(const std::string& str) 
{
    return  str.size() < 64 &&
            str[0] <= 57 &&
            str[str.size() - 1] >= 48;
}

void replace_even(std::string& str) 
{
    std::string result = "";
    for (char item : str)
    {
        if (std::stoi(&item) % 2)
            result += item;
        else
            result += "KB";
    }
    str = result;
}

int sum_odds(const std::string& str)
{
    int result = 0;
    for (char item : str) 
    {
        if (item >= 48 && item <= 57) 
        {
            result += std::stoi(&item);
        }
    }
    return result;
}

void* prepare_data(void*) 
{
    std::string str = "";
    while(true) 
    {
        std::cin >> str;
        std::sort(str.rbegin(), str.rend());
        if (check(str)) 
        {
            replace_even(str);
            gData.set_data(str);
        } 
        else 
        {
            std::cout << "Only numbers allowed and length no more than 64 symbols" << '\n';
        }
    }
}

void* process_data(void*) 
{
    struct addrinfo hints;
    struct addrinfo* servinfo;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    int gai = getaddrinfo(NULL, "1234", &hints, &servinfo);
    if (gai != 0) 
    {
        std::cout<< "getaddrinfo: " << gai_strerror(gai) << std::endl;
        exit(1);
    }

    int client_socket = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
    if (client_socket == -1) 
    {
        perror("socket");
        exit(1);
    }

    int cnct = connect(client_socket, servinfo->ai_addr, servinfo->ai_addrlen);
    if (cnct == -1) 
    {
        perror("connect (server didn't started?)");
        close(client_socket);
        exit(1);
    }

    while(true) 
    {
	    std::string data(gData.get_data());
	    std::cout << "Data: " << data.c_str() << std::endl;
        std::stringstream ss;
        ss << sum_odds(data);
        std::string sm = ss.str();
        cnct = connect(client_socket, servinfo->ai_addr, servinfo->ai_addrlen);
        int snd = send(client_socket, sm.c_str(), sizeof(sm), 0);
        if (snd == 0) 
        {
            perror("send");
            exit(1);
        }
    }
    freeaddrinfo(servinfo);
    close(client_socket);
}
