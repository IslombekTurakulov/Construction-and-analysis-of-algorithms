#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::getline;
using std::string;

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string input;
    string sides;
    getline(cin, input);
    int result = 0;
    for (auto &symbol : input) {
        if (symbol == 'B') {
            ++result;
        } else {
            sides += symbol;
        }
    }
    char next_side = 'L';
    sides += "//";
    for (int index = 0; index < sides.length() - 1; ++index) {
        if (next_side == 'L') {
            if (sides[index] == 'L' && sides[index + 1] == 'L') {
                ++result;
                next_side = 'R';
                ++index;
            } else if (sides[index] == 'L' && sides[index + 1] == 'R') {
                ++result;
            } else if ((sides[index] == 'L' && sides[index + 1] == '/') || sides[index] == '/') {
                ++result;
                break;
            }
        }
        if (next_side == 'R') {
            if (sides[index] == 'R' && sides[index + 1] == 'R') {
                ++result;
                next_side = 'L';
                ++index;
            } else if (sides[index] == 'R' && sides[index + 1] == 'L') {
                ++result;
            } else if (sides[index] == 'R') {
                ++result;
            }
        }
    }
    cout << result;
    return 0;
}
