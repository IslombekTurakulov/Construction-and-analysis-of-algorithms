#include <iostream>
#include <string>
#include <unordered_map>

using std::cin;
using std::cout;
using std::string;
using std::unordered_map;

constexpr int kNum = -1;

void tempInitialize(const string &input, int *arr);

void showTheInformation(const string &first_input, const string &second_input,
                        unordered_map<char, char> *codes, int start);

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string first_input, second_input;
    cin >> first_input >> second_input;
    int *first_arr = new int[static_cast<int>(first_input.length())];
    int *second_arr = new int[static_cast<int>(second_input.length())];
    tempInitialize(first_input, first_arr);
    tempInitialize(second_input, second_arr);
    unordered_map<char, int> first_map;
    unordered_map<char, char> second_map;
    for (int index = static_cast<int>(second_input.length() - 1); index > -1; --index) {
        char code = second_input[index];
        if (first_map.count(code)) {
            second_arr[index] = first_map[code] - index;
        }
        first_map[code] = index;
    }
    first_map.clear();
    int start = -1;
    int first_index = 0;
    while (first_index < static_cast<int>(first_input.length())) {
        if (first_map.count(first_input[first_index])) {
            int code = first_map[first_input[first_index]];
            first_arr[code] = first_index - code;
        }
        first_map[first_input[first_index]] = first_index;
        if (first_index > static_cast<int>(second_input.length() - 2)) {
            bool flag = true;
            int second_index = first_index - static_cast<int>(second_input.length()) + 1;
            while (second_index < first_index + 1) {
                auto temp_index =
                    second_index - first_index + static_cast<int>(second_input.length()) - 1;
                if (second_arr[temp_index] != first_arr[second_index]) {
                    flag = false;
                    break;
                }
                ++second_index;
            }
            if (flag) {
                start = first_index - static_cast<int>(second_input.length()) + 1;
                break;
            }
        }
        ++first_index;
    }
    showTheInformation(first_input, second_input, &second_map, start);
    delete[] first_arr;
    delete[] second_arr;
    return 0;
}

void showTheInformation(const string &first_input, const string &second_input,
                        unordered_map<char, char> *codes, int start) {
    if (start != -1) {
        cout << "Possible"
             << "\n";
        auto index = 0;
        while (index < static_cast<int>(second_input.length())) {
            (*codes)[first_input[start + index]] = second_input[index];
            ++index;
        }
        index = 0;
        while (index < static_cast<int>(first_input.length())) {
            if ((*codes).count(first_input[index])) {
                cout << (*codes)[first_input[index]];
            } else {
                cout << '?';
            }
            ++index;
        }
    } else {
        cout << "Impossible"
             << "\n";
    }
}

void tempInitialize(const string &input, int *arr) {
    for (int i = 0; i < input.length(); ++i) {
        arr[i] = kNum;
    }
}
