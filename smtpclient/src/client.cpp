#include <iostream>
#include "client.h"

namespace smtpclient
{
    using namespace std;
    
    Client::Client(const char *host = "localhost")
    {
        hostname = host;
        buffer = "GET / HTTP/1.0\r\nConnection: close\r\n\r\n";
    }

    void Client::fill()
    {
        hostinfo = gethostbyname(hostname);
        if(!hostinfo) {
            cerr << "no host: " << hostname << endl;
            exit(1);
        }

        servinfo = getservbyname("http", "tcp");
        if(!servinfo) {
            cerr << "no http service\n";
            exit(1);
        }
    }

    void Client::send()
    {
        char readBuffer[512];

        fill();

        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        address.sin_family = AF_INET;
        address.sin_port = servinfo->s_port;
        address.sin_addr = *(struct in_addr *)*hostinfo->h_addr_list;
        len = sizeof(address);

        result = connect(sockfd, (struct sockaddr *)&address, len);
        if(result == -1) {
            perror("opps: http");
            exit(1);
        }

        write(sockfd, &buffer, sizeof(buffer));
        result = read(sockfd, &readBuffer, sizeof(readBuffer));
        readBuffer[result] = '\0';
        cout << readBuffer << endl;

        close(sockfd);
    }
}