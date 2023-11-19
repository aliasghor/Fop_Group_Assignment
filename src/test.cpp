#include <iostream>

using namespace std;

int main() {
    int index = 0;

    while (index < 5) {
        for (int i = 0; i < 10; i++) {
            cout << "Tikus" << endl;
        }
        cout << "Gerry" << endl;
        index++;
    }

    cin.get();
    return 0;
}