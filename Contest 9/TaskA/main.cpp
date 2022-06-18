#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <string>

using std::cin;
using std::cout;
using std::map;
using std::set;
using std::sort;
using std::string;
using std::vector;

struct Vertex {
    string code;
    char symbol;
    int counter;

    Vertex() = default;

    Vertex(char first, int second) {
        symbol = first;
        counter = second;
    }
};

void showData(const string& input, map<char, string>* map_code, const set<char>& set_text,
              vector<Vertex>* arr_of_text, int64_t index);

int compare(const Vertex& first, const Vertex& second) {
    return first.counter <= second.counter
               ? first.counter == second.counter && first.symbol < second.symbol ? 1 : 0
               : 1;
}

int main() {
    map<char, int> map_text;
    map<char, string> map_code;
    set<char> set_text;
    string code = "0";
    string input;
    int64_t index = 0;
    cin >> input;
    for (auto item : input) {
        map_text.insert_or_assign(item, 0);
        set_text.insert(item);
    }
    for (auto item : input) {
        map_text.insert_or_assign(item, map_text.at(item) + 1);
    }
    vector<Vertex> arr_of_text(set_text.size(), Vertex());
    for (auto item : set_text) {
        arr_of_text[index] = Vertex(item, map_text.at(item));
        ++index;
    }
    sort(arr_of_text.begin(), arr_of_text.end(), compare);
    map_code.insert_or_assign(arr_of_text[0].symbol, code);
    arr_of_text[0].code = code;
    for (index = 1; index < arr_of_text.size(); ++index) {
        const auto& current_code = '1' + code;
        if (arr_of_text[index].counter == arr_of_text[index - 1].counter) {
            if (index != arr_of_text.size() - 1) {
                map_code.insert_or_assign(arr_of_text[index].symbol, current_code);
                arr_of_text[index].code = current_code;
            } else {
                arr_of_text[index].code = code.substr(0, code.length() - 1) + '1';
                map_code.insert_or_assign(arr_of_text[index].symbol,
                                          code.substr(0, code.length() - 1) + '1');
            }
        } else {
            map_code.insert_or_assign(arr_of_text[index].symbol, current_code);
            arr_of_text[index].code = current_code;
        }
        code = current_code;
    }
    showData(input, &map_code, set_text, &arr_of_text, index);
    return 0;
}

void showData(const string& input, map<char, string>* map_code, const set<char>& set_text,
              vector<Vertex>* arr_of_text, int64_t index) {
    string result;
    for (index = 0; index < input.length(); ++index) {
        result += (*map_code).at(input[index]);
    }
    cout << set_text.size() << " " << result.length() << "\n";
    for (const auto& item : (*arr_of_text)) {
        cout << item.symbol << ": " << item.code << "\n";
    }
    cout << result << "\n";
}
