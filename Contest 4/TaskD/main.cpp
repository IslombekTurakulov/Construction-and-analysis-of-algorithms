#include <iostream>
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::string;
using std::vector;

int main() {
    int length;
    bool has_middle = false;
    string input;
    string start;
    string middle;
    string end;
    cin >> length;
    vector<int> counter(26, 0);
    for (int i = 0; i < length; ++i) {
        char symbol;
        cin >> symbol;
        ++counter[symbol - 'A'];
    }
    for (char first_index = 'A'; first_index <= 'Z'; ++first_index) {
        int second_index = 0;
        while (second_index < counter[first_index - 'A'] / 2) {
            start += first_index;
            ++second_index;
        }
    }
    for (char first_index = 'A'; first_index <= 'Z'; ++first_index) {
        if (counter[first_index - 'A'] % 2 == 1) {
            middle += first_index;
            has_middle = true;
            break;
        }
    }
    start += middle;
    for (int iteration = start.length() - (has_middle ? 2 : 1); iteration >= 0; --iteration) {
        end += start[iteration];
    }
    cout << start << end << "\n";
    return 0;
}
