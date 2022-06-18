#include <algorithm>
#include <iostream>
#include <map>
#include <string>

using std::cin;
using std::cout;
using std::map;
using std::string;

void decode(map<string, char> *dict, int length, const string &encoded_text);

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    map<string, char> dict;
    string letter, code;
    int diffs, length;
    cin >> diffs >> length;
    for (int index = 0; index < diffs; ++index) {
        cin >> letter >> code;
        dict.insert_or_assign(code, letter[0]);
    }
    string encoded_text;
    cin >> encoded_text;
    decode(&dict, length, encoded_text);
    return 0;
}

void decode(map<string, char> *dict, int length, const string &encoded_text) {
    string result;
    for (int index = 0; index < length; ++index) {
        result += encoded_text[index];
        if ((*dict).find(result) != (*dict).end()) {
            cout << (*dict).at(result) << "";
            result.clear();
        }
    }
}
