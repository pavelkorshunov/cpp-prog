#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void show_vector(const int &rr);

int main(int argc, char **argv) {
    vector<int> rating(5);
    rating[0] = 3;
    rating[1] = 6;
    rating[2] = 4; // остальные 2 значения будут инициализированы нулями

    cout << "raiting elements: \n";
    for(short i = 0; i < 5; i++) {
        cout << rating[i] << "\n";
    }

    cout << "rating size: " << rating.size() << "\n";

    // Добавление элемента в конец
    rating.push_back(12);

    cout << "raiting elements: \n";
    for(short i = 0; i < 6; i++) {
        cout << rating[i] << "\n";
    }
    cout << "rating size: " << rating.size() << "\n";

    // удаляем элементы между ating.begin() + 3 и rating.end() - 1
    rating.erase(rating.begin() + 3, rating.end() - 1);

    // итератор
    vector<int>::iterator pr;

    cout << "raiting elements: \n";
    for(pr = rating.begin(); pr != rating.end(); pr++) {
        cout << *pr << "\n";
    }
    cout << "rating size: " << rating.size() << "\n";

    vector<int> old_rating(rating); // конструктор копирования по умолчанию
    old_rating.pop_back();

    cout << "old_rating elements: \n";
    for_each(old_rating.begin(), old_rating.end(), show_vector);

    cout << "old_rating size: " << old_rating.size() << "\n";

    return 0;
}

void show_vector(const int &rr) {
    cout << rr << "\n";
}