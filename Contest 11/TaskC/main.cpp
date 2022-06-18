#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::max;
using std::string;
using std::vector;

void checkStonesValidation(int **multi_arr, vector<int> arr_stones, vector<int> *result, int length,
                           int stones) {
    if (multi_arr[length][stones] == 0) {
        return;
    } else if (multi_arr[length - 1][stones] == multi_arr[length][stones]) {
        checkStonesValidation(multi_arr, arr_stones, result, length - 1, stones);
    } else {
        checkStonesValidation(multi_arr, arr_stones, result, length - 1,
                              stones - arr_stones[length - 1]);
        if (arr_stones[length - 1] != 0) {
            (*result).push_back(arr_stones[length - 1]);
        }
    }
}

vector<int> methDynamic(vector<int> arr_stones, int length, int stones) {
    vector<int> result;
    int **multi_arr = new int *[length + 1];
    for (int i = 0; i <= length; ++i) {
        multi_arr[i] = new int[stones + 1];
    }
    for (int i = 0; i <= stones; ++i) {
        multi_arr[0][i] = 0;
    }
    for (int i = 1; i <= length; ++i) {
        for (int j = 0; j <= stones; ++j) {
            multi_arr[i][j] = multi_arr[i - 1][j];
            if (j - arr_stones[i - 1] >= 0) {
                multi_arr[i][j] = max(multi_arr[i][j],
                                      multi_arr[i - 1][j - arr_stones[i - 1]] + arr_stones[i - 1]);
            }
        }
    }
    checkStonesValidation(multi_arr, arr_stones, &result, length, stones);
    for (int i = 0; i <= length; ++i) {
        delete[] multi_arr[i];
    }
    delete[] multi_arr;
    return result;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int length;
    int stones;
    cin >> length >> stones;
    vector<int> arr_stones(length);
    for (int i = 0; i < length; ++i) {
        cin >> arr_stones[i];
    }
    vector<int> result = methDynamic(arr_stones, length, stones);
    int sum_of_stones = 0;
    for (int i = 0; i < result.size(); ++i) {
        sum_of_stones += result.at(i);
    }
    cout << sum_of_stones << "\n";
    cout << result.size() << "\n";
    for (int i = 0; i < result.size(); ++i) {
        cout << result.at(i) << " ";
    }
    return 0;
}
