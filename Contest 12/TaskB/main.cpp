#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::min;
using std::string;
using std::vector;

void upperSides(int rows, int columns, const vector<vector<char>>& array,
                vector<vector<int>>* upper_left, vector<vector<int>>* upper_right);

void bottomSides(int rows, int columns, const vector<vector<char>>& array,
                 vector<vector<int>>* bottom_left, vector<vector<int>>* bottom_right);
int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int rows, columns;
    cin >> rows >> columns;
    vector<vector<char>> array(rows, vector<char>(columns));
    vector<vector<int>> upper_left(rows, vector<int>(columns));
    vector<vector<int>> upper_right(rows, vector<int>(columns));
    vector<vector<int>> bottom_left(rows, vector<int>(columns));
    vector<vector<int>> bottom_right(rows, vector<int>(columns));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            cin >> array[i][j];
        }
    }
    // Смотрим верхние индексы
    upperSides(rows, columns, array, &upper_left, &upper_right);
    // Смотрим нижние индексы
    bottomSides(rows, columns, array, &bottom_left, &bottom_right);
    int64_t sum = 0;
    for (int k = 0; k < rows; ++k) {
        for (int j = 0; j < columns; ++j) {
            sum += min(min(upper_left[k][j], upper_right[k][j]),
                       min(bottom_left[k][j], bottom_right[k][j]));
        }
    }
    cout << sum << "\n";
    return 0;
}
void bottomSides(int rows, int columns, const vector<vector<char>>& array,
                 vector<vector<int>>* bottom_left, vector<vector<int>>* bottom_right) {
    for (int bottom_row = rows - 1; bottom_row >= 0; --bottom_row) {
        for (int col_left = 0; col_left < columns; ++col_left) {
            int col_right = columns - col_left - 1;
            if (bottom_row == rows - 1 || col_left == 0) {
                (*bottom_left)[bottom_row][col_left] = 1;
            } else if (array[bottom_row + 1][col_left] == array[bottom_row][col_left] &&
                       array[bottom_row][col_left - 1] == array[bottom_row][col_left]) {
                (*bottom_left)[bottom_row][col_left] = min((*bottom_left)[bottom_row + 1][col_left],
                                                           (*bottom_left)[bottom_row][col_left - 1]);
                ++(*bottom_left)[bottom_row][col_left];
            } else {
                (*bottom_left)[bottom_row][col_left] = 1;
            }
            if (bottom_row == rows - 1 || col_right == columns - 1) {
                (*bottom_right)[bottom_row][col_right] = 1;
            } else if (array[bottom_row + 1][col_right] == array[bottom_row][col_right] &&
                       array[bottom_row][col_right + 1] == array[bottom_row][col_right]) {
                (*bottom_right)[bottom_row][col_right] = min((*bottom_right)[bottom_row + 1][col_right],
                                                             (*bottom_right)[bottom_row][col_right + 1]);
                ++(*bottom_right)[bottom_row][col_right];
            } else {
                (*bottom_right)[bottom_row][col_right] = 1;
            }
        }
    }
}

void upperSides(int rows, int columns, const vector<vector<char>>& array,
                vector<vector<int>>* upper_left, vector<vector<int>>* upper_right) {
    for (int up_row = 0; up_row < rows; ++up_row) {
        for (int col_left = 0; col_left < columns; ++col_left) {
            int col_right = columns - col_left - 1;
            if (up_row == 0 || col_left == 0) {
                (*upper_left)[up_row][col_left] = 1;
            } else if (array[up_row - 1][col_left] == array[up_row][col_left] &&
                       array[up_row][col_left - 1] == array[up_row][col_left]) {
                (*upper_left)[up_row][col_left] =
                    min((*upper_left)[up_row - 1][col_left], (*upper_left)[up_row][col_left - 1]);
                ++(*upper_left)[up_row][col_left];
            } else {
                (*upper_right)[up_row][col_left] = 1;
            }
            if (up_row == 0 || col_right == columns - 1) {
                (*upper_right)[up_row][col_right] = 1;
            } else if (array[up_row - 1][col_right] == array[up_row][col_right] &&
                       array[up_row][col_right + 1] == array[up_row][col_right]) {
                (*upper_right)[up_row][col_right] =
                    min((*upper_right)[up_row - 1][col_right], (*upper_right)[up_row][col_right + 1]);
                ++(*upper_right)[up_row][col_right];
            } else {
                (*upper_right)[up_row][col_right] = 1;
            }
        }
    }
}
