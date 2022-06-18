#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

using std::cin;
using std::cout;
using std::swap;
using std::vector;

void sortArray(int *arr, int length, int max) {
    int64_t exp = 1;
    int *second = new int[length];
    for (; max / exp > 0;) {
        vector<int64_t> box(256, 0);
        int64_t iteration;
        for (iteration = 0; iteration < length; ++iteration) {
            ++box[arr[iteration] / exp % 256];
        }
        for (iteration = 1; iteration < 256; ++iteration) {
            box[iteration] += box[iteration - 1];
        }
        for (iteration = length - 1; iteration >= 0; --iteration) {
            second[--box[arr[iteration] / exp % 256]] = arr[iteration];
        }
        for (iteration = 0; iteration < length; ++iteration) {
            arr[iteration] = second[iteration];
        }
        exp *= 256;
    }
}

int upperBound(const int arr[], int size, int key) {
    int left = -1;
    int right = size;
    while (right != left + 1) {
        int middle = (left + right) / 2;
        key >= arr[middle] ? left = middle : right = middle;
    }
    return right;
}

int lowerBound(const int arr[], int size, int key) {
    int left = -1;
    int right = size;
    while (right != left + 1) {
        int middle = (left + right) / 2;
        key <= arr[middle] ? right = middle : left = middle;
    }
    return left;
}

int main() {
    int amount_of_intervals;
    std::cin >> amount_of_intervals;
    int *interval_start = new int[amount_of_intervals];
    int *interval_end = new int[amount_of_intervals];
    int max_start = 0;
    int max_end = 0;
    for (int i = 0; i < amount_of_intervals; ++i) {
        cin >> interval_start[i];
        cin >> interval_end[i];
        max_start = max_start < interval_start[i] ? interval_start[i] : max_start;
        max_end = max_end < interval_end[i] ? interval_end[i] : max_end;
    }
    sortArray(interval_start, amount_of_intervals, max_start);
    sortArray(interval_end, amount_of_intervals, max_end);
    char first = 0;
    while (first != '!') {
        int request;
        cin >> first;
        if (first == '!') {
            break;
        }
        cin >> request;
        int upper = upperBound(interval_start, amount_of_intervals, request);
        int lower = lowerBound(interval_end, amount_of_intervals, request);
        cout << "! " << upper - lower - 1 << std::endl;
        cout.flush();
    }
    delete[] interval_start;
    delete[] interval_end;
    return 0;
}
