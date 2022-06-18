#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using std::cin;
using std::cout;
using std::swap;
using std::vector;

vector<int> initialize(int length);

void showData(int length, const vector<int> &vector, int swaps);

int main() {
    int length;
    cin >> length;
    vector<int> vector = initialize(length);
    int swaps = 0;
    for (int first_index = 1; first_index < length - 1; ++first_index) {
        bool check;
        int second_loop_len = length - first_index - 1;
        for (int second_index = 0; second_index <= second_loop_len; ++second_index) {
            if (vector[second_index] > vector[second_index + 1]) {
                swap(vector[second_index], vector[second_index + 1]);
                check = true;
                ++swaps;
            }
        }
        if (!check) {
            break;
        }
    }
    showData(length, vector, swaps);
    return 0;
}

void showData(int length, const vector<int> &vector, int swaps) {
    for (int i = 0; i < length; ++i) {
        cout << vector[i] << " ";
    }
    cout << "\n" << swaps << "\n";
}

vector<int> initialize(int length) {
    vector<int> vector(length);
    for (int i = 0; i < length; ++i) {
        cin >> vector[i];
    }
    return vector;
}
