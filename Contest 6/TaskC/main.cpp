#include <iostream>
#include <algorithm>
#include <utility>

using std::cin;
using std::cout;
using std::swap;

int partition(int *arr, int first, int last) {
    int pivot = arr[last];
    int index = first;
    for (int i = first; i < last; ++i) {
        if (arr[i] <= pivot) {
            swap(arr[i], arr[index]);
            ++index;
        }
    }
    swap(arr[index], arr[last]);
    return index;
}

void quickSort(int *arr, int left, int right, int *count) {
    if (left < right) {
        int pivot = partition(arr, left, right);
        quickSort(arr, left, pivot - 1, count);
        quickSort(arr, pivot + 1, right, count);
        ++(*count);
    }
}

int main() {
    int length;
    cin >> length;
    int *arr = new int[length];
    if (length == 0) {
        cout << 0 << "\n";
        delete[] arr;
        return 0;
    }
    for (int i = 0; i < length; ++i) {
        cin >> arr[i];
    }
    int left = 0;
    int right = length - 1;
    int count = -1;
    quickSort(arr, left, right, &count);
    if (length == 1) {
        cout << 0 << "\n";
    } else {
        cout << count << "\n";
    }
    for (int i = 0; i < length; ++i) {
        cout << arr[i] << " ";
    }
    delete[] arr;
    return 0;
}
