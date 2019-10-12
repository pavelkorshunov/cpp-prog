#include <iostream>
#include <fstream>
#include <string>

int main () {
    using namespace std;
    string filename;

    cout << "Enter filename: ";
    cin >> filename;

    ofstream first(filename.c_str());
    first << "My first file in cpp lang" << endl;

    cout << "Enter your favorite number1 and number2: ";

    int number1, number2;
    cin >> number1 >> number2;
    first << "Your first number is " << number1 << endl;
    first << "Your second number is " << number2;

    first.close();

    return 0;
}