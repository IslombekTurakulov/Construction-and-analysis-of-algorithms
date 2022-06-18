#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::max;
using std::reverse;
using std::sort;
using std::string;
using std::vector;

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int64_t red_length, green_length, blue_length;
    cin >> red_length;
    cin >> green_length;
    cin >> blue_length;
    vector<vector<int64_t>> end_arr(green_length + 1, vector<int64_t>(blue_length + 1));
    vector<vector<int64_t>> begin_arr(green_length + 1, vector<int64_t>(blue_length + 1));
    vector<int64_t> red_array(red_length);
    vector<int64_t> green_array(green_length);
    vector<int64_t> blue_array(blue_length);
    for (int64_t i = 0; i < red_length; ++i) {
        cin >> red_array[i];
    }
    for (int64_t i = 0; i < green_length; ++i) {
        cin >> green_array[i];
    }
    for (int64_t i = 0; i < blue_length; ++i) {
        cin >> blue_array[i];
    }
    sort(red_array.begin(), red_array.end());
    sort(green_array.begin(), green_array.end());
    sort(blue_array.begin(), blue_array.end());
    reverse(red_array.begin(), red_array.end());
    reverse(green_array.begin(), green_array.end());
    reverse(blue_array.begin(), blue_array.end());
    int64_t maximum = 0;
    for (int64_t red = 0; red < red_length + 1; ++red) {
        for (int64_t green = 0; green < green_length + 1; ++green) {
            for (int64_t blue = 0; blue < blue_length + 1; ++blue) {
                if ((red > 0) && (green > 0)) {
                    begin_arr[green][blue] =
                        max(begin_arr[green][blue],
                            end_arr[green - 1][blue] + red_array[red - 1] * green_array[green - 1]);
                }
                if ((red > 0) && (blue > 0)) {
                    begin_arr[green][blue] =
                        max(begin_arr[green][blue],
                            end_arr[green][blue - 1] + red_array[red - 1] * blue_array[blue - 1]);
                }
                if ((green > 0) && (blue > 0)) {
                    begin_arr[green][blue] = max(begin_arr[green][blue],
                                                 begin_arr[green - 1][blue - 1] +
                                                     green_array[green - 1] * blue_array[blue - 1]);
                }
                maximum = max(maximum, begin_arr[green][blue]);
            }
        }
        for (int64_t i = 0; i < green_length + 1; ++i) {
            for (int64_t j = 0; j < blue_length + 1; ++j) {
                end_arr[i][j] = begin_arr[i][j];
                begin_arr[i][j] = 0;
            }
        }
    }
    cout << maximum;
    return 0;
}