#pragma once

#include <netinet/in.h>
#include <sys/socket.h>
#include <cstdlib>
#include <string>
#include <netdb.h>
#include <unistd.h>
#include <cstdio>

namespace smtpclient
{
    class Client
    {
        private:
            const char *hostname;
            int sockfd, len, result;
            std::string buffer;
            sockaddr_in address;
            servent *servinfo;
            hostent *hostinfo;

            void fill();

        public:
            Client(const char *host);
            void send();
    };
}