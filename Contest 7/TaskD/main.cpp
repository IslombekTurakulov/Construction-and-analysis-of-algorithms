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

int levenshteinDistance(const string &first, const string &second, int first_length,
                        int second_length) {
    int *array = new int[(first_length + 1) * (second_length + 1)];
    for (int i = 0; i <= first_length; ++i) {
        array[i * (second_length + 1)] = i;
    }
    for (int i = 0; i <= second_length; ++i) {
        array[i] = i;
    }
    for (int index = 1; index <= second_length; ++index) {
        for (int i = 1; i <= first_length; ++i) {
            int c = array[(i - 1) * (second_length + 1) + (index - 1)];
            if (first[i - 1] == second[index - 1]) {
                array[(i) * (second_length + 1) + (index)] = c;
            } else {
                int a = array[(i - 1) * (second_length + 1) + (index)];
                int b = array[i * (second_length + 1) + (index - 1)];
                array[i * (second_length + 1) + index] =
                    min(a, min(b, c)) + (first[i - 1] == second[index - 1] ? 0 : 1);
            }
        }
    }
    int dist = array[first_length * (second_length + 1) + second_length];
    delete[] array;
    return dist;
}

int main() {
    string length;
    getline(cin, length);
    int n = atoi(length.c_str());
    for (int iteration = 0; iteration < n; ++iteration) {
        string s;
        string t;
        std::getline(cin, s);
        std::getline(cin, t);
        cout << levenshteinDistance(s, t, s.length(), t.length())
             << (iteration == n - 1 ? "" : " ");
    }
    return 0;
}
