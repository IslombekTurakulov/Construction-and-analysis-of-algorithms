#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>

using std::cin;
using std::cout;
using std::pow;
using std::string;

char hammingCode(int index, const string &input) {
    int counter = 0;
    int result = 0;
    bool flag = true;
    for (int i = index - 1; i < input.length(); ++i) {
        if (counter == index) {
            counter = 0;
            flag = !flag;
        }
        if (flag) {
            result += input[i];
        }
        ++counter;
    }
    return result % 2 == 1 ? '1' : '0';
}

int main() {
    string input;
    std::getline(cin, input);
    int counter = 0;
    while (static_cast<int>(pow(2, counter)) <= input.length()) {
        ++counter;
    }
    for (int i = 0; i < counter; ++i) {
        int powed_num = static_cast<int>(pow(2, i));
        input = input.substr(0, powed_num - 1) + '0' + input.substr(powed_num - 1, input.length());
    }
    for (int i = 0; i < counter; ++i) {
        int powed_num = static_cast<int>(pow(2, i));
        input[powed_num - 1] = hammingCode(powed_num, input);
    }
    cout << input;

    return 0;
}