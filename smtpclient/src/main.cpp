#include <iostream>
#include "client.h"

using namespace smtpclient;

int main(int argc, char **argv)
{   
    if(argc > 1) {
        Client client = Client(*(argv + 1));
        client.send();
    } else {
        std::cout << "argv not initial\n";
    }

    return 0;
}