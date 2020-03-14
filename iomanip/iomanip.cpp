#include <iostream>
#include <iomanip>
using namespace std;

//Манипуляторы потока

int main() {
    int seconds;
    cin >> seconds;

    int hour, minutes, sec;
    hour = (seconds / 3600) % 24;
    minutes = (seconds / 60) % 60;
    sec = seconds % 60;

    cout << hour << ":" << setw(2) << setfill('0') << minutes << ":" << setw(2) << setfill('0') << sec;
}