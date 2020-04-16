#include <iostream>
#include <set>
using namespace std;

int main()
{
    set <int> num;
    num.insert(1);
    num.insert(5);
    num.insert(3);

    for(auto now : num) {
        cout << now << " ";
    }
    return 0;
}