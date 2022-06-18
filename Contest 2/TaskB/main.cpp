#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

int upperBound(const int *data, int value, int length) {
    int right = length;
    int left = -1;
    while (right - left > 1) {
        int middle = (left + right) / 2;
        if (data[middle] <= value) {
            left = middle;
        } else {
            right = middle;
        }
    }
    return right;
}

int lowerBound(const int *data, int value, int length) {
    int right = length;
    int left = -1;
    while (right - left > 1) {
        int middle = (left + right) / 2;
        if (data[middle] < value) {
            left = middle;
        } else {
            right = middle;
        }
    }
    return right;
}

int main() {
    int first_length;
    int second_length;
    cin >> first_length >> second_length;
    int *first = new int[(first_length)];
    int *second = new int[(second_length)];
    for (int i = 0; i < first_length; ++i) {
        cin >> first[i];
    }
    for (int i = 0; i < second_length; ++i) {
        cin >> second[i];
    }
    for (int i = 0; i < second_length; ++i) {
        int key = second[i];
        int lower = lowerBound(first, key, first_length);
        int upper = upperBound(first, key, first_length);
        if (lower < first_length && first[lower] == key) {
            cout << lower + 1 << " " << upper << "\n";
        } else {
            cout << 0 << "\n";
        }
    }
    delete[] first;
    delete[] second;
    return 0;
}
