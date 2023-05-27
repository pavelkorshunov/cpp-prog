#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")
//#pragma warning(disable: 4996)

#define DEFAULT_PORT "27015" // порт для прослушки
#define LENGHT_BUFFER 512 // размер буфера
#define DEFAULT_HOST "127.0.0.1" // хост

using namespace std;

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "Russian");
       
    WSADATA wsa_data;
    WORD DLL_version = MAKEWORD(2, 2);

    SOCKET connect_socket = INVALID_SOCKET;

    int i_result;
    char r_buffer[LENGHT_BUFFER];

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

    connect_socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (connect_socket == INVALID_SOCKET) {
        cout << "Error at socket(): " << WSAGetLastError() << endl;
        freeaddrinfo(result);
        WSACleanup();
        exit(1);
    }

    i_result = connect(connect_socket, result->ai_addr, (int)result->ai_addrlen);
    if (i_result == SOCKET_ERROR) {
        cout << "connet fail" << endl;

        closesocket(connect_socket);
        connect_socket = INVALID_SOCKET;
        freeaddrinfo(result);
        WSACleanup();
        exit(1);
    }
    else {
        cout << "Connet with host: " << DEFAULT_HOST << " in port: " << DEFAULT_PORT << endl;
    }

    freeaddrinfo(result);

    // закрываем сокет на отправку данных
    i_result = shutdown(connect_socket, SD_SEND);
    if (i_result == SOCKET_ERROR) {
        cout << "shutdown failed with error: " << WSAGetLastError() << endl;
        closesocket(connect_socket);
        WSACleanup();
        return 1;
    }

    i_result = recv(connect_socket, r_buffer, LENGHT_BUFFER, 0);
    if (i_result > 0)
        cout << r_buffer << endl;
    else if (i_result == 0)
        cout << "Connection closed" << endl;
    else
        cout << "recv failed with error: " << WSAGetLastError() << endl;

    closesocket(connect_socket);
    WSACleanup();

    system("pause");
    return 0;
}
