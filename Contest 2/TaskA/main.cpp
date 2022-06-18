#include <iostream>

using std::cin;
using std::cout;

int main() {
    int second_max = 0;
    int first_max = 0;
    int input;
    while (cin >> input) {
        if (input == 0) {
            if (second_max > first_max) {
                cout << second_max << "\n";
                cout << first_max << "\n";
            } else {
                cout << first_max << "\n";
                cout << second_max << "\n";
            }
            break;
        }
        if (input > first_max) {
            if (first_max < second_max) {
                first_max = second_max;
                second_max = input;
            } else {
                second_max = input;
            }
        } else {
            if (second_max < input) {
                second_max = input;
            }
        }
    }
    return 0;
}
