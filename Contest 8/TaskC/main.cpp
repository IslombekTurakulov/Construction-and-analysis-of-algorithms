#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::string;
using std::vector;

vector<int> prefixFunction(string s) {
    int n = s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = pi[j - 1];
        }
        if (s[i] == s[j]) {
            ++j;
        }
        pi[i] = j;
    }
    return pi;
}
int suffixLink(vector<int> arr, int presses, string input, int size, int capacity) {
    int max_depth = 0;
    int **vector_aut = new int *[size];
    for (int i = 0; i < size; ++i) {
        vector_aut[i] = new int[capacity];
    }
    for (int iteration = 0; iteration < size; ++iteration) {
        for (int j = 0; j < capacity; ++j) {
            int first = iteration + (j == input[iteration]);
            bool second = 'a' + j == input[iteration];
            vector_aut[iteration][j] =
                iteration <= 0 || second ? first : vector_aut[arr[iteration - 1]][j];
            int depth_level = iteration - vector_aut[iteration][j];
            if (max_depth < depth_level) {
                max_depth = depth_level;
            }
        }
    }
    for (int i = 0; i < size; ++i) {
        delete[] vector_aut[i];
    }
    delete[] vector_aut;
    return size + presses * max_depth;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string input;
    int n, a, k;
    cin >> n >> a >> k;
    cin >> input;
    vector<int> arr = prefixFunction(input);
    cout << suffixLink(arr, k, input, n, a);
    return 0;
}
