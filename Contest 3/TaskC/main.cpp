#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using std::cin;
using std::cout;
using std::swap;
using std::vector;

std::pair<bool, vector<int>> swapMethod(int first_index, vector<int> vector);

void showData(int length, const vector<int> &vector, int counter);

vector<int> initialize(int length);

int main() {
    int length;
    int counter = 0;
    cin >> length;
    vector<int> vector = initialize(length);
    for (int first_index = 1; first_index < length; ++first_index) {
        auto result = swapMethod(first_index, vector);
        bool changed = result.first;
        vector = result.second;
        if (!changed) {
            ++counter;
        }
    }
    showData(length, vector, counter);
    return 0;
}

vector<int> initialize(int length) {
    vector<int> vector(length);
    for (int i = 0; i < length; ++i) {
        cin >> vector[i];
    }
    return vector;
}

void showData(int length, const vector<int> &vector, int counter) {
    for (int i = 0; i < length; ++i) {
        cout << vector[i] << " ";
    }
    cout << "\n" << counter << "\n";
}

std::pair<bool, vector<int>> swapMethod(int first_index, vector<int> vector) {
    bool changed = false;
    for (int j = first_index; j > 0 && vector[j - 1] > vector[j]; --j) {
        swap(vector[j], vector[j - 1]);
        changed = true;
    }
    return std::make_pair(changed, vector);
}
