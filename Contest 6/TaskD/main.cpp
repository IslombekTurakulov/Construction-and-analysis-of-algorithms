/*
 * Ubuntu
 * sudo apt update
 * sudo apt upgrade
 * sudo apt install make git zlib1g-dev libssl-dev gperf php cmake clang-10 libc++-dev libc++abi-dev
 * Откуда была взята реализация: https://www.cs.dartmouth.edu/~doug/aqsort.c
 */

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>

int *value;

int sortKiller(int length, int *array);

int main() {
    int n = 32768;
    int *array = new int[n];
    int comparisons = sortKiller(n, array);
    std::cout << "comparisons: " << comparisons << std::endl;
    // Можно ещё увеличить кол-во данных просто добавив 32767 для каждого числа.
    for (comparisons = 0; comparisons < n; ++comparisons) {
        // printf("%d\n", array[comparisons] + 32767);
        printf("%d\n", array[comparisons]);
    }
    delete[] array;
    return 0;
}

int sortKiller(int length, int *array) {
    int solids = 0;
    int comparisons = 0;
    int pivot_candidate = 0;
    int gas = length - 1;
    value = array;
    std::vector<int> ptr(length);
    for (int index = 0; index < length; ++index) {
        value[index] = gas;
        ptr[index] = index;
    }
    std::sort(ptr.begin(), ptr.end(), [&](int x, int y) {
        comparisons++;
        if (value[x] == gas && value[y] == gas) {
            value[(x == pivot_candidate ? x : y)] = solids++;
        }
        if (value[x] == gas) {
            pivot_candidate = x;
        } else if (value[y] == gas) {
            pivot_candidate = y;
        }
        return value[x] < value[y];
    });
    for (int i = 1; i < length; ++i) {
        assert(value[ptr[i]] == value[ptr[i - 1]] + 1);
    }
    return comparisons;
}
