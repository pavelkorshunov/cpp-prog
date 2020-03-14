#include <iostream>
#include <iomanip>
using namespace std;

// Манипуляторы потока
// Программа выводит количество часов, минут и секунд. На вход получает например 129700 секунд на выход выводит 12:01:40

int main() {
    int seconds;
    cin >> seconds;

    int hour, minutes, sec;
    hour = (seconds / 3600) % 24;
    minutes = (seconds / 60) % 60;
    sec = seconds % 60;

    cout << hour << ":" << setw(2) << setfill('0') << minutes << ":" << setw(2) << setfill('0') << sec;
}
