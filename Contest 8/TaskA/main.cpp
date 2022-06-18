#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::max;
using std::min;
using std::string;

void zFunction(string s, int *arr) {
    int *z = new int[s.length()];
    int n = s.length();
    for (int i = 0; i < n; ++i) {
        z[i] = 0;
    }
    for (int i = 1; i < n; ++i) {
        if (arr[i]) {
            z[i - arr[i] + 1] = arr[i];
        }
    }
    for (int i = 1; i < n; ) {
        int j, v;
        for (j = 1; j < z[i] && (v = min(z[j], z[i] - j)) >= z[i + j] ; ++j) {
            z[i + j] = v;
        }
        i += j;
    }
}

int main() {
    string input;
    std::getline(cin, input);
    int *arr = new int[input.length()];
    zFunction(input, arr);
    for (int i = 0; i < input.length(); ++i) {
        cout << arr[i] << ' ';
    }
    delete[] arr;
    return 0;
}
