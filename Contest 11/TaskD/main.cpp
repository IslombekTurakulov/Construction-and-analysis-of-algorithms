// https://e-maxx.ru/algo/mst_prim
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::string;
using std::vector;

int getMinimalKey(vector<int> key, vector<bool> mst_set, int length);

void primMST(vector<vector<int>> const &array);

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int rooms_in_dormitory;
    cin >> rooms_in_dormitory;
    if (rooms_in_dormitory != 0) {
        int *cost_of_internet = new int[rooms_in_dormitory];
        int *cost_of_each_neighbour = new int[rooms_in_dormitory - 1];
        for (int i = 0; i < rooms_in_dormitory; ++i) {
            cin >> cost_of_internet[i];
        }
        for (int i = 0; i < rooms_in_dormitory - 1; ++i) {
            cin >> cost_of_each_neighbour[i];
        }
        vector<vector<int>> matrix(rooms_in_dormitory + 1, vector<int>(rooms_in_dormitory + 1, 0));
        // Заполняем грани
        for (int i = 1; i < matrix.size(); ++i) {
            matrix[0][i] = cost_of_internet[i - 1];
            matrix[i][0] = cost_of_internet[i - 1];
        }
        // Заполняем диагональ
        for (int i = 2; i < matrix.size(); ++i) {
            matrix[i][i - 1] = cost_of_each_neighbour[i - 2];
            matrix[i - 1][i] = cost_of_each_neighbour[i - 2];
        }
        primMST(matrix);
        delete[] cost_of_each_neighbour;
        delete[] cost_of_internet;
    } else {
        cout << 0;
    }
    return 0;
}

int getMinimalKey(vector<int> key, vector<bool> mst_set, int length) {
    int min = INT32_MAX;
    int get_min_index;
    for (int i = 0; i < length; ++i) {
        if (!mst_set[i] && key[i] < min) {
            min = key[i];
            get_min_index = i;
        }
    }
    return get_min_index;
}

void primMST(const vector<vector<int>> &array) {
    vector<bool> mst_set(array.size(), false);
    vector<int> parent(array.size());
    vector<int> key(array.size(), INT32_MAX);
    key[0] = 0;
    parent[0] = -1;
    for (int i = 0; i < array.size() - 1; ++i) {
        int min_key = getMinimalKey(key, mst_set, array.size());
        mst_set[min_key] = true;
        for (int j = 0; j < array.size(); ++j) {
            if (array[min_key][j] && !mst_set[j] && (array[min_key][j] < key[j])) {
                parent[j] = min_key;
                key[j] = array[min_key][j];
            }
        }
    }
    int sum = 0;
    for (int i = 1; i < array.size(); ++i) {
        sum += array[i][parent[i]];
    }
    cout << sum;
}
