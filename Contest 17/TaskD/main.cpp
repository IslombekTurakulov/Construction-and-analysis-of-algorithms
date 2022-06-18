#include "BigIntegerUtils2.h"
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::string;
using std::vector;

void nextPerm(vector<BigInteger> *arr, int tasks, int tasks_per_day) {
    for (int i = tasks_per_day - 1; i >= 0; --i) {
        if (arr->at(i) < tasks - tasks_per_day + i + 1) {
            arr->at(i)++;
            for (int j = i + 1; j < tasks_per_day; ++j) {
                arr->at(j) = arr->at(j - 1) + 1;
            }
            break;
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int tasks, tasks_per_day;
    string task_index;
    cin >> tasks >> task_index >> tasks_per_day;
    vector<BigInteger> vec(tasks);
    std::iota(vec.begin(), vec.end(), 1);
    auto result = stringToBigInteger(task_index);
    while (result - 1 > 1) {
        nextPerm(&vec, tasks, tasks_per_day);
        result--;
    }
    for (int i = 0; i < tasks_per_day; ++i) {
        if (i + 1 == tasks_per_day) {
            cout << vec[i];
        } else {
            cout << vec[i] << " ";
        }
    }
    return 0;
}
