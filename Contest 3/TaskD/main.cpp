#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using std::cin;
using std::cout;
using std::swap;
using std::vector;

vector<int> initialize(int length, vector<int> vector);

int methodSearch(const vector<int> &vector, int left, int right, int temp);

void showResult(int length, int swaps, const vector<int> &vector);

int main() {
    int length;
    int swaps = 0;
    cin >> length;
    vector<int> vector(length);
    if (length != 0) {
        vector = initialize(length, vector);
        for (int first_index = 1; first_index < length; ++first_index) {
            if (vector[first_index - 1] > vector[first_index]) {
                int left = 0;
                int right = first_index - 1;
                int temp = vector[first_index];
                left = methodSearch(vector, left, right, temp);
                for (int index = first_index - 1; index >= left; --index) {
                    ++swaps;
                    vector[index + 1] = vector[index];
                }
                vector[left] = temp;
            }
        }
    }
    showResult(length, swaps, vector);
    return 0;
}

void showResult(int length, int swaps, const vector<int> &vector) {
    for (int i = 0; i < length; ++i) {
        cout << vector[i] << " ";
    }
    cout << "\n" << swaps << "\n";
}

int methodSearch(const vector<int> &vector, int left, int right, int temp) {
    do {
        int middle = (left + right) / 2;
        vector[middle] <= temp ? (left = middle + 1) : (right = middle - 1);
    } while (left <= right);
    return left;
}

vector<int> initialize(int length, vector<int> vector) {
    for (int i = 0; i < length; ++i) {
        cin >> vector[i];
    }
    return vector;
}
