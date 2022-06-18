#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>

using std::cin;
using std::cout;
using std::pair;
using std::swap;
using std::vector;

void binSearch(int data, int sh, const int *arr_res, const int *map_index, const int *arr);

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
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int residents;
    int shelters;
    cin >> residents;
    int *arr_residents = new int[residents];
    for (int i = 0; i < residents; ++i) {
        cin >> arr_residents[i];
    }
    cin >> shelters;
    int *arr = new int[shelters];
    int max = 0;
    for (int i = 0; i < shelters; ++i) {
        cin >> arr[i];
        max = max < arr[i] ? arr[i] : max;
    }
    int *map_index = new int[max + 1];
    for (int i = 0; i < shelters; ++i) {
        map_index[arr[i]] = i + 1;
    }
    int index = shelters / 2 - 1;
    while (index >= 0) {
        fixHeap(arr, shelters, index);
        --index;
    }
    index = shelters - 1;
    while (index >= 0) {
        swap(arr[0], arr[index]);
        fixHeap(arr, index, 0);
        --index;
    }
    binSearch(residents, shelters, arr_residents, map_index, arr);
    delete[] arr;
    delete[] map_index;
    delete[] arr_residents;
    return 0;
}

void binSearch(int data, int sh, const int *arr_res, const int *map_index, const int *arr) {
    for (int index = 0; index < data; ++index) {
        int left = 0;
        int right = sh - 1;
        while (right - left > 1) {
            int middle = (left + right) / 2;
            if (arr_res[index] > arr[middle]) {
                left = middle;
            } else {
                right = middle;
            }
        }
        int shelter_id = (arr_res[index] > (arr[left] + arr[right]) / 2 ? right : left);
        cout << map_index[arr[shelter_id]] << " ";
    }
}
