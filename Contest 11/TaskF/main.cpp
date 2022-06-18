#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::string;
using std::vector;

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int width_of_woods, length;
    cin >> width_of_woods >> length;
    vector<int> temp_arr(length + 2);
    temp_arr[length + 1] = width_of_woods;
    for (int i = 1; i < length + 1; ++i) {
        cin >> temp_arr[i];
    }
    vector<vector<int>> array(length + 2, vector<int>(length + 2));
    for (int i = 1; i < length + 2; ++i) {
        for (int j = i - 2; j > -1; --j) {
            array[j][i] = INT32_MAX;
            for (int k = j + 1; k < i; ++k) {
                array[j][i] = std::min(array[j][i], array[j][k] + array[k][i]);
            }
            array[j][i] += temp_arr[i] - temp_arr[j];
        }
    }
    cout << array.front().back() << '\n';
    return 0;
}
