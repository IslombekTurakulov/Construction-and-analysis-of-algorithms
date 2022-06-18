#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using std::cin;
using std::cout;
using std::swap;
using std::vector;

vector<int64_t> initialize(int64_t length);

int64_t searchMin(int64_t length, const vector<int64_t> &vec, int64_t index, int64_t minimum);

void showData(int64_t length, int64_t swaps, const vector<int64_t> &vector);

int main() {
    int64_t length;
    int64_t swaps = 0;
    cin >> length;
    vector<int64_t> vector = initialize(length);
    if (length != 0) {
        for (int64_t first_index = 0; first_index < length; ++first_index) {
            int64_t minimum = vector[first_index];
            int64_t temp_index = searchMin(length, vector, first_index, minimum);
            if (first_index != temp_index) {
                swap(vector[first_index], vector[temp_index]);
                ++swaps;
            }
        }
    }
    showData(length, swaps, vector);
    return 0;
}

void showData(int64_t length, int64_t swaps, const vector<int64_t> &vector) {
    for (int64_t i = 0; i < length; ++i) {
        cout << vector[i] << " ";
    }
    cout << "\n" << swaps << "\n";
}

int64_t searchMin(int64_t length, const vector<int64_t> &vec, int64_t index, int64_t minimum) {
    int64_t temp_index = index;
    for (int64_t second_index = index; second_index < length; ++second_index) {
        if (vec[second_index] < minimum) {
            minimum = vec[second_index];
            temp_index = second_index;
        }
    }
    return temp_index;
}

vector<int64_t> initialize(int64_t length) {
    std::vector<int64_t> vector(length);
    for (int64_t i = 0; i < length; ++i) {
        cin >> vector[i];
    }
    return vector;
}
