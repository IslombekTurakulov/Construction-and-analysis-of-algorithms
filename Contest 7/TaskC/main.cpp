#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::min;
using std::string;
using std::vector;

int wagnerFischer(string s, string t, int **arr) {
    for (int i = 1; i <= s.size(); ++i) {
        for (int j = 1; j <= t.size(); ++j) {
            int first = min(arr[i - 1][j] + 1, arr[i][j - 1] + 1);
            if (s[i - 1] == t[j - 1]) {
                arr[i][j] = min(first, arr[i - 1][j - 1]);
            } else {
                arr[i][j] = min(first, arr[i - 1][j - 1] + 1);
            }
        }
    }
    return arr[s.size()][t.size()];
}

int main() {
    string s;
    string t;
    getline(cin, s);
    getline(cin, t);
    int **array = new int *[s.size() + 1];
    for (int i = 0; i <= s.size(); ++i) {
        array[i] = new int[t.size() + 1];
        array[i][0] = i;
    }
    for (int j = 0; j <= t.size(); ++j) {
        array[0][j] = j;
    }
    cout << wagnerFischer(s, t, array);
    for (int i = 0; i <= s.size(); ++i) {
        delete[] array[i];
    }
    delete[] array;
    return 0;
}
