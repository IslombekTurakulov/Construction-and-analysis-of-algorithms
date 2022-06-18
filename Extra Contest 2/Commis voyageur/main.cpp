// Рассказывают как сделать правильно
// http://galyautdinov.ru/post/zadacha-kommivoyazhera
// https://www.hse.ru/data/2010/10/14/1223122527/DA_Algorithms.pdf
#include <cmath>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

int64_t pow(const int64_t &x) {
    return (x * x);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int64_t length, coord_x = 1;
    int64_t coord_x_distance = INT64_MAX;
    cin >> length;
    vector<int64_t> arr_coords_x(length);
    vector<int64_t> arr_coords_y(length);
    vector<bool> visited(length);
    vector<int64_t> path;
    for (int i = 0; i < length; ++i) {
        cin >> arr_coords_x[i] >> arr_coords_y[i];
        visited[i] = false;
        for (int j = 0; j < i; ++j) {
            int64_t dist = sqrtl(pow((arr_coords_x[i] - arr_coords_x[j])) +
                                 pow((arr_coords_y[i] - arr_coords_y[j])));
            if (dist < coord_x_distance) {
                coord_x_distance = dist;
                coord_x = i;
            }
        }
    }
    visited[coord_x] = true;
    path.push_back(coord_x);
    while (path.size() != length) {
        int64_t current_path = path[path.size() - 1];
        int64_t coord_y_distance = INT64_MAX;
        int temp_num = -1;
        for (int i = 0; i < length; ++i) {
            if (!visited[i]) {
                int64_t dist = sqrtl(pow((arr_coords_x[current_path] - arr_coords_x[i])) +
                                     pow((arr_coords_y[current_path] - arr_coords_y[i])));
                if (dist < coord_y_distance) {
                    coord_y_distance = dist;
                    temp_num = i;
                }
            }
        }
        path.push_back(temp_num);
        visited[temp_num] = true;
    }
    for (int i = 0; i < length; ++i) {
        cout << path[i] + 1 << " ";
    }
    return 0;
}
