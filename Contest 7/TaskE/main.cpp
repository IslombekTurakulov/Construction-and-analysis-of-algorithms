#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::max;
using std::min;
using std::string;
using std::vector;

int wagnerLevenshtein(string s, string t, int **arr) {
    for (int i = 1; i <= s.size(); ++i) {
        for (int j = 1; j <= t.size(); ++j) {
            int a = min((arr[i - 1][j] + 1), (arr[i][j - 1] + 1));
            int c = arr[i - 1][j - 1] + (s[i - 1] == t[j - 1] ? 0 : 1);
            bool length = i > 1 && j > 1;
            arr[i][j] = min(a, length && s[i - 2] == t[j - 1] && s[i - 1] == t[j - 2]
                                   ? min(c, arr[i - 2][j - 2] + 1)
                                   : c);
        }
    }
    return arr[s.size()][t.size()];
}

int main() {
    int length;
    cin >> length;
    for (int iteration = 0; iteration < length; ++iteration) {
        string s, t;
        cin >> s >> t;
        int **arr = new int *[s.size() + 1];
        for (int i = 0; i <= s.size(); ++i) {
            arr[i] = new int[t.size() + 1];
            arr[i][0] = i;
        }
        for (int j = 0; j <= t.size(); ++j) {
            arr[0][j] = j;
        }
        cout << wagnerLevenshtein(s, t, arr) << (iteration == length - 1 ? "" : " ");
        for (int i = 0; i <= s.size(); ++i) {
            delete[] arr[i];
        }
        delete[] arr;
    }
    return 0;
}
