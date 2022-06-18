#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using std::cin;
using std::cout;
using std::max;
using std::string;
using std::vector;

int getResult(string x, string y) {
    int **array = new int *[x.length() + 1];
    for (int64_t i = 0; i < x.length() + 1; ++i) {
        array[i] = new int[y.length() + 1];
    }
    for (int64_t i = x.length() - 1; i >= 0; --i) {
        for (int64_t j = y.length() - 1; j >= 0; --j) {
            int first = array[i + 1][j + 1] + 1;
            int second = max(array[i + 1][j], array[i][j + 1]);
            array[i][j] = x[i] == y[j] ? first : second;
        }
    }
    int res = array[0][0];
    for (int64_t i = 0; i < x.length() + 1; ++i) {
        delete[] array[i];
    }
    delete[] array;
    return res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string first;
    string second;
    std::getline(cin, first);
    std::getline(cin, second);
    cout << getResult(first, second);
    return 0;
}
