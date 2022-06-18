#include <iostream>
#include <vector>

using namespace std;

void printArray(int A[], int size) {
    for (int i = 0; i < size; i++) {
        cout << A[i] << " ";
    }
    cout << endl;
}

// Function to join left and right subarray
void join(int arr[], int left[], int right[],
          int l, int m, int r) {
    int i;
    for (i = 0; i <= m - l; i++)
        arr[i] = left[i];

    for (int j = 0; j < r - m; j++) {
        arr[i + j] = right[j];
    }
}

// Function to store alternate elements in
// left and right subarray
int split(int arr[], int left[], int right[],
          int l, int m, int r) {
    for (int i = 0; i <= m - l; i++)
        left[i] = arr[i * 2];

    for (int i = 0; i < r - m; i++)
        right[i] = arr[i * 2 + 1];
}

// Function to generate Worst Case
// of Merge Sort
int generateWorstCase(int arr[], int l,
                      int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        // Create two auxiliary arrays
        int left[m - l + 1];
        int right[r - m];

        // Store alternate array elements
        // in left and right subarray
        split(arr, left, right, l, m, r);

        // Recurse first and second halves
        generateWorstCase(left, l, m);
        generateWorstCase(right, m + 1, r);

        // Join left and right subarray
        join(arr, left, right, l, m, r);
    }
}


int main() {
    int *array = new int[32768];
    for (int i = 32768u - 1; i >= 0; --i) {
        array[i] = i;
    }
    /*for (int i = 0; i < 32768u/2; ++i) {
        array[i + 1] = i;
    }
    for (int i = 32768 / 2; i >= 0; --i) {
        array[i - 1] = i;
    }
    for (int i = 0; i < 32768; ++i) {
        if (i % 6 == 0) {
            int index = 32768 % (i + 1);
            swap(array[i], array[index]);
        }
    }*/
    generateWorstCase(array, 0, 32767);
    printArray(array, 32768);
    return 0;
}
