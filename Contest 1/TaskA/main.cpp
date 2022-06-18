#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

int main() {
    int length;
    cin >> length;
    vector<int> vector;
    vector.reserve(1000);
    int erased = 0;
    int index = 0;
    int temp_erased = -1;
    while (index < length) {
        cin >> vector[index];
        ++index;
    }
    index = 0;
    while (index < length) {
        int ball = vector[index];
        if (temp_erased == ball) {
            ++erased;
        } else if (vector.size() >= 2) {
            if (vector[vector.size() - 1] == ball && vector[vector.size() - 2] == ball) {
                while (!vector.empty() && vector[vector.size() - 1] == ball) {
                    vector.pop_back();
                    ++erased;
                }
                temp_erased = ball;
                ++erased;
            } else {
                temp_erased = -1;
                vector.push_back(ball);
            }
        } else {
            temp_erased = -1;
            vector.push_back(ball);
        }
        ++index;
    }
    cout << erased << "\n";
    return 0;
}
