#include <iostream>
#include "connection.h"

int main() 
{
    Connection connect;

    while(true) 
    {
        connect.receive();
        std::string result = connect.get_data();
	    std::cout << "Data: " << result << " ";
        if (result.size() > 2 && !(std::stoi(result) % 32)) 
        {
            std::cout << "Correct data\n" << std::endl;
        } 
        else 
        {
            std::cout << "Wrong data\n";
        }
    }
    return 0;
}