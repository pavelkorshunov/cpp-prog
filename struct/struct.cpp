#include <iostream>

struct product
{
    char name[20];
    float price;
};

int main()
{
    using namespace std;
    product ball =
    {
        "Ball",
        1.88
    };

    cout << "Name - " << ball.name << " price: " << ball.price << endl;

    return 0;
}