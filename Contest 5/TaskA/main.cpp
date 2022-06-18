#include <iostream>

using std::cin;
using std::cout;

bool isHeap(int64_t arr[], int64_t index, int64_t length) {
    int64_t left = (index * 2) + 1;
    int64_t right = (index * 2) + 2;
    if (left < length) {
        if (arr[left] > arr[index] || !isHeap(arr, left, length)) {
            return false;
        }
    }
    if (right < length) {
        if (arr[right] > arr[index] || !isHeap(arr, right, length)) {
            return false;
        }
    }
    return true;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int64_t length;
    cin >> length;
    auto *arr = new int64_t[length];
    int64_t left = 0, right = length;
    for (int64_t index = 0; index < length; ++index) {
        cin >> arr[index];
    }
    while (left < right) {
        int64_t middle = (left + right) / 2;
        isHeap(arr, 0, middle + 1) ? (left = middle + 1) : (right = middle);
    }
    cout << right - 1 << "\n";
    delete[] arr;
    return 0;
}
