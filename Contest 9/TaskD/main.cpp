#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

void showData(const string &input, int64_t length, int64_t index);

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string input;
    cin >> input;
    input = '0' + input;
    int64_t length = input.size();
    int64_t current_position = 0;
    int64_t index = 1;
    while (index < length) {
        if (input[index] == '1') {
            current_position ^= index;
        }
        ++index;
    }
    if (current_position != 0 && current_position < length) {
        input[current_position] = input[current_position] == '0' ? '1' : '0';
    }
    index = 1;
    showData(input, length, index);
    return 0;
}

void showData(const string &input, int64_t length, int64_t index) {
    while (index < length) {
        if (index & (index - 1)) {
            cout << input[index];
        }
        ++index;
    }
}
