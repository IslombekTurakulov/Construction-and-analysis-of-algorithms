#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::string;
using std::unordered_map;
using std::vector;

vector<int> encoding(string input) {
    unordered_map<string, int> map_ascii_chars;
    vector<int> output_code;
    string temp_first;
    for (int i = 0; i <= 127; ++i) {
        string temp_str;
        temp_str += static_cast<char>(i);
        map_ascii_chars[temp_str] = i;
    }
    temp_first += input[0];
    int code = 128;
    for (int index = 0; index < input.length(); ++index) {
        string temp_second;
        if (index != input.length() - 1) {
            temp_second += input[index + 1];
        }
        if (map_ascii_chars.find(temp_first + temp_second) != map_ascii_chars.end()) {
            temp_first = temp_first + temp_second;
        } else {
            output_code.push_back(map_ascii_chars[temp_first]);
            map_ascii_chars[temp_first + temp_second] = code;
            code++;
            temp_first = temp_second;
        }
    }
    output_code.push_back(map_ascii_chars[temp_first]);
    return output_code;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string text;
    std::getline(cin, text);
    vector<int> result = encoding(text);
    cout << result.size() << "\n";
    for (int i = 0; i < result.size(); ++i) {
        cout << result[i] << " ";
    }
    cout << "\n";
    return 0;
}
