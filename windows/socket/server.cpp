#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")
//#pragma warning(disable: 4996)

#define DEFAULT_PORT "27015" // порт для прослушки
#define LENGHT_BUFFER 512 // размер буфера
#define DEFAULT_HOST "127.0.0.1" // хост

using namespace std;

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "Russian");

    WSADATA wsa_data;
    WORD DLL_version = MAKEWORD(2, 2);
    int i_result;
    int send_result;
    char s_buffer[LENGHT_BUFFER] = "Test server running. All data send!";

    SOCKET listen_socket = INVALID_SOCKET;
    SOCKET client_socket = INVALID_SOCKET;

    // Подключение DLL библиотеки WS2_32.dll
    i_result = WSAStartup(DLL_version, &wsa_data);
    if (i_result != 0) {
        cout << "WSAStartup failed: " << i_result << endl;
        exit(1);
    }

    // Заполняем структуру addrinfo
    struct addrinfo* result = NULL;
    struct addrinfo address;

    ZeroMemory(&address, sizeof(address));
    address.ai_family = AF_INET;
    address.ai_socktype = SOCK_STREAM;
    address.ai_protocol = IPPROTO_TCP;

    i_result = getaddrinfo(DEFAULT_HOST, DEFAULT_PORT, &address, &result);
    if (i_result != 0) {
        cout << "getaddrinfo failed with error: " << i_result << endl;
        WSACleanup();
        exit(1);
    }

    listen_socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (listen_socket == INVALID_SOCKET) {
        cout << "Error at socket(): " << WSAGetLastError() << endl;
        freeaddrinfo(result);
        WSACleanup();
        exit(1);
    }

    i_result = bind(listen_socket, result->ai_addr, (int)result->ai_addrlen);
    if (i_result == SOCKET_ERROR) {
        cout << "bind failed" << endl;
        freeaddrinfo(result);
        WSACleanup();
        exit(1);
    }

    freeaddrinfo(result);

    // Открываем сокет на прослушку
    i_result = listen(listen_socket, SOMAXCONN);
    if (i_result == SOCKET_ERROR) {
        cout << "listen failed with error: " << WSAGetLastError() << endl;
        closesocket(listen_socket);
        WSACleanup();
        exit(1);
    }
    else {
        cout << "Server running" << endl;
        cout << "Не переживайте я к вам подключаюсь" << endl;
    }

    // Принимаем клиентский сокет
    client_socket = accept(listen_socket, NULL, NULL);
    if (client_socket == INVALID_SOCKET) {
        cout << "accept failed with error: " << WSAGetLastError() << endl;
        closesocket(client_socket);
        WSACleanup();
        exit(1);
    }

    // Серверный сокет больше не нужен
    closesocket(listen_socket);

    send_result = send(client_socket, s_buffer, LENGHT_BUFFER, 0);
    if (send_result == SOCKET_ERROR) {
        cout << "send failed with error: " << WSAGetLastError() << endl;
        closesocket(client_socket);
        WSACleanup();
        exit(1);
    }

    // Заканчиваем обмен данными и отключаемся
    i_result = shutdown(client_socket, SD_SEND);
    if (i_result == SOCKET_ERROR) {
        cout << "shutdown failed with error: " << WSAGetLastError() << endl;
        closesocket(client_socket);
        WSACleanup();
        exit(1);
    }

    closesocket(client_socket);
    WSACleanup();

    return 0;
}
