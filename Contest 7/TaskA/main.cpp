#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::string;
using std::vector;

void getSubstrings(string pat, string substring, vector<int> *res) {
    int temp_num = 0;
    int *array_br = new int[pat.size()];
    array_br[0] = 0;
    for (int i = 1; i < pat.size(); ++i) {
        while ((temp_num > 0) && (pat[i] != pat[temp_num])) {
            temp_num = array_br[temp_num - 1];
        }
        if (pat[i] == pat[temp_num]) {
            ++temp_num;
        }
        array_br[i] = temp_num;
    }
    int index = 0;
    for (int i = 0; i < substring.length(); ++i) {
        while ((index > 0) && (pat[index] != substring[i])) {
            index = array_br[index - 1];
        }
        if (pat[index] == substring[i]) {
            ++index;
        }
        if (index == pat.length()) {
            (*res).push_back(i - pat.length() + 1);
        }
    }
    delete[] array_br;
}

int main() {
    string pattern;
    string substring;
    getline(cin, pattern);
    getline(cin, substring);
    vector<int> array;
    getSubstrings(pattern, substring, &array);
    cout << array.size() << "\n";
    for (int i = 0; i < array.size(); ++i) {
        cout << array.at(i) << "\n";
    }
    return 0;
}