#include <iostream>
#include <algorithm>
#include <utility>

using std::cin;
using std::cout;
using std::swap;

std::pair<int, int> partition(int *arr, int low, int high) {
    int partition = arr[(low + high) / 2];
    int right = high;
    int left = low;
    while (left <= right) {
        while (arr[left] < partition) {
            ++left;
        }
        while (arr[right] > partition) {
            --right;
        }
        if (left > right) {
            break;
        }
        swap(arr[left], arr[right]);
        ++left;
        --right;
    }
    return std::make_pair(left, right);
}

void quickSort(int *arr, int left, int right, int *counter) {
    if (left < right) {
        auto pivot = partition(arr, left, right);
        if (left < pivot.second) {
            ++(*counter);
            quickSort(arr, left, pivot.second, counter);
        }
        if (pivot.first < right) {
            ++(*counter);
            quickSort(arr, pivot.first, right, counter);
        }
    }
}

int main() {
    int length;
    cin >> length;
    int *arr = new int[length];
    for (int i = 0; i < length; ++i) {
        cin >> arr[i];
    }
    int left = 0;
    int right = length - 1;
    int counter = 0;
    quickSort(arr, left, right, &counter);
    cout << counter << "\n";
    for (int i = 0; i < length; ++i) {
        cout << arr[i] << " ";
    }
    delete[] arr;
    return 0;
}
