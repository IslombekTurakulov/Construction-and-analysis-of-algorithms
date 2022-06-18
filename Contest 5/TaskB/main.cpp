// Знаю мы рекурсию толком не проходили в этом курсе
// Но я использовал псевдо-код с лекции. Aboba
#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>

using std::cin;
using std::cout;
using std::swap;
using std::vector;

void fixHeap(int *heap_arr, int length, int index) {
    int max_index = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    if (left < length && heap_arr[left] > heap_arr[max_index]) {
        max_index = left;
    }
    if (right < length && heap_arr[right] > heap_arr[max_index]) {
        max_index = right;
    }
    if (max_index != index) {
        swap(heap_arr[index], heap_arr[max_index]);
        fixHeap(heap_arr, length, max_index);
    }
}

int main() {
    int size;
    cin >> size;
    int *arr = new int[size];
    int index = -1;
    while (index < size - 1) {
        cin >> arr[++index];
    }
    index = size / 2 - 1;
    while (index >= 0) {
        fixHeap(arr, size, index);
        --index;
    }
    index = size - 1;
    while (index >= 0) {
        swap(arr[0], arr[index]);
        fixHeap(arr, index, 0);
        --index;
    }
    index = 0;
    while (index < size) {
        cout << arr[index] << " ";
        ++index;
    }
    delete[] arr;
    return 0;
}
