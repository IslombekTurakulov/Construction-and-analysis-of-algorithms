#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::string;
using std::unordered_map;
using std::vector;

unordered_map<int, string>& initializeFromArray(unordered_map<int, string>* map_integer_chars);

void decodeFromArray(vector<int> array) {
    unordered_map<int, string> map_integer_chars;
    string temp_first, temp_second;
    int count = 128, temp_first_num = array[0];
    map_integer_chars = initializeFromArray(&map_integer_chars);
    temp_first = map_integer_chars[temp_first_num];
    temp_second += temp_first[0];
    cout << temp_first;
    for (int index = 0; index < array.size() - 1; ++index) {
        int length = array[index + 1];
        if (map_integer_chars.find(length) == map_integer_chars.end()) {
            temp_first = map_integer_chars[temp_first_num];
            temp_first = temp_first + temp_second;
        } else {
            temp_first = map_integer_chars[length];
        }
        cout << temp_first;
        temp_second = "";
        temp_second += temp_first[0];
        map_integer_chars[count] = map_integer_chars[temp_first_num] + temp_second;
        temp_first_num = length;
        ++count;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int length;
    cin >> length;
    vector<int> result(length);
    for (int i = 0; i < length; ++i) {
        cin >> result.at(i);
    }
    decodeFromArray(result);
    return 0;
}

unordered_map<int, string>& initializeFromArray(unordered_map<int, string>* map_integer_chars) {
    for (int i = 0; i <= 127; ++i) {
        string temp_str;
        temp_str += static_cast<char>(i);
        (*map_integer_chars)[i] = temp_str;
    }
    return (*map_integer_chars);
}
