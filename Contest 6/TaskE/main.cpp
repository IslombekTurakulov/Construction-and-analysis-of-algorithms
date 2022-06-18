#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>

using std::cin;
using std::cout;
using std::find;
using std::pair;
using std::swap;
using std::vector;

void next(int total, const vector<pair<int, char>> &arr, int *last_red, int *last_green,
          int *last_blue, vector<int> *next_red, vector<int> *next_green, vector<int> *next_blue);

void prev(int total, const vector<pair<int, char>> &arr, vector<int> *prev_red,
          vector<int> *prev_green, vector<int> *prev_blue, int *last_red, int *last_green,
          int *last_blue);

pair<int, int> partition(vector<pair<int, char>> *arr, int low, int high) {
    int partition = (*arr)[(high + low) / 2].first;
    int right = high;
    int left = low;
    while (left <= right) {
        while ((*arr)[left].first < partition) {
            ++left;
        }
        while ((*arr)[right].first > partition) {
            --right;
        }
        if (left > right) {
            break;
        }
        swap((*arr)[left], (*arr)[right]);
        ++left;
        --right;
    }
    return std::make_pair(left, right);
}

void quickSort(vector<pair<int, char>> *arr, int left, int right) {
    if (left < right) {
        auto pivot = partition(arr, left, right);
        if (left < pivot.second) {
            quickSort(arr, left, pivot.second);
        }
        if (pivot.first < right) {
            quickSort(arr, pivot.first, right);
        }
    }
}

int64_t func(int64_t red, int64_t green, int64_t blue) {
    int64_t first = red - green;
    int64_t second = green - blue;
    int64_t third = red - blue;
    return first * first + second * second + third * third;
}

void initializeArr(int start, int length, vector<pair<int, char>> *array, char color) {
    for (int j = start; j < length; ++j) {
        int input;
        cin >> input;
        (*array)[j].first = input;
        (*array)[j].second = color;
    }
}

int checker(const vector<pair<int, char>> &array, bool *flag, int j, char color) {
    int value = 0;
    if (!(*flag) && array[j].second == color) {
        value = j;
        (*flag) = true;
    }
    return value;
}

vector<int> checkColor(int size, char color, vector<pair<int, char>> const &gems,
                       vector<int> result, vector<int> const &prev, vector<int> const &next) {
    for (int i = 0; i < size; ++i) {
        if (gems[i].second == color && (prev[i] != -1 && next[i] != -1)) {
            int first_red = gems[result[0]].first;
            int first_green = gems[result[1]].first;
            int first_blue = gems[result[2]].first;
            const int64_t &first = func(first_red, first_green, first_blue);
            const int64_t &second = func(gems[i].first, gems[prev[i]].first, gems[next[i]].first);
            if (first > second) {
                result = {i, prev[i], next[i]};
            }
        }
    }
    return result;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int amount_of_tests;
    cin >> amount_of_tests;
    for (int times = 0; times < amount_of_tests; ++times) {
        int length_red, length_green, length_blue;
        cin >> length_red >> length_green >> length_blue;
        int total = length_red + length_green + length_blue;
        vector<pair<int, char>> arr(total);
        // Инициализация переменных
        initializeArr(0, length_red, &arr, 'r');
        initializeArr(length_red, length_green + length_red, &arr, 'g');
        initializeArr(length_green + length_red, total, &arr, 'b');
        // Сортировка
        quickSort(&arr, 0, total - 1);
        int first_red, first_green, first_blue;
        bool is_red = false, is_green = false, is_blue = false;
        // Берём первый элемент
        for (int index = 0; index < total; ++index) {
            if (!is_red) {
                first_red = checker(arr, &is_red, index, 'r');
            }
            if (!is_green) {
                first_green = checker(arr, &is_green, index, 'g');
            }
            if (!is_blue) {
                first_blue = checker(arr, &is_blue, index, 'b');
            }
            if (is_red && is_green && is_blue) {
                break;
            }
        }
        vector<int> result = {first_red, first_green, first_blue};
        int last_red = -1, last_green = -1, last_blue = -1;
        vector<int> prev_red, next_red;
        vector<int> prev_green, next_green;
        vector<int> prev_blue, next_blue;

        prev(total, arr, &prev_red, &prev_green, &prev_blue, &last_red, &last_green, &last_blue);
        next(total, arr, &last_red, &last_green, &last_blue, &next_red, &next_green, &next_blue);

        std::reverse(next_red.begin(), next_red.end());
        std::reverse(next_green.begin(), next_green.end());
        std::reverse(next_blue.begin(), next_blue.end());
        vector<vector<int>> answers = {
            checkColor(total, 'r', arr, result, prev_green, next_blue),
            checkColor(total, 'r', arr, result, prev_blue, next_green),
            checkColor(total, 'g', arr, result, prev_red, next_blue),
            checkColor(total, 'g', arr, result, prev_blue, next_red),
            checkColor(total, 'b', arr, result, prev_red, next_green),
            checkColor(total, 'b', arr, result, prev_green, next_red),
        };
        for (int i = 0; i < 6; ++i) {
            const int64_t &first =
                func(arr[result[0]].first, arr[result[1]].first, arr[result[2]].first);
            const int64_t &second =
                func(arr[answers[i][0]].first, arr[answers[i][1]].first, arr[answers[i][2]].first);
            if (first > second) {
                result = answers[i];
            }
        }
        vector<int> ans(3);
        for (int index = 0; index < total; ++index) {
            bool is_exist = find(result.begin(), result.end(), index) != result.end();
            if ((arr[index].second == 'r') && is_exist) {
                ans[0] = index;
                continue;
            }
            if ((arr[index].second == 'g') && is_exist) {
                ans[1] = index;
                continue;
            }
            if ((arr[index].second == 'b') && is_exist) {
                ans[2] = index;
            }
        }
        cout << arr[ans[0]].first << " " << arr[ans[1]].first << " " << arr[ans[2]].first << '\n';
    }
    return 0;
}

void prev(int total, const vector<pair<int, char>> &arr, vector<int> *prev_red,
          vector<int> *prev_green, vector<int> *prev_blue, int *last_red, int *last_green,
          int *last_blue) {
    for (int index = 0; index < total; ++index) {
        (*prev_red).push_back(*last_red);
        (*prev_green).push_back(*last_green);
        (*prev_blue).push_back(*last_blue);
        if (arr[index].second == 'r') {
            *last_red = index;
            continue;
        }
        if (arr[index].second == 'g') {
            *last_green = index;
            continue;
        }
        if (arr[index].second == 'b') {
            *last_blue = index;
        }
    }
}

void next(int total, const vector<pair<int, char>> &arr, int *last_red, int *last_green,
          int *last_blue, vector<int> *next_red, vector<int> *next_green, vector<int> *next_blue) {
    *last_red = -1, *last_green = -1, *last_blue = -1;
    for (int index = total - 1; index >= 0; --index) {
        (*next_red).push_back(*last_red);
        (*next_green).push_back(*last_green);
        (*next_blue).push_back(*last_blue);
        if (arr[index].second == 'r') {
            *last_red = index;
            continue;
        }
        if (arr[index].second == 'g') {
            *last_green = index;
            continue;
        }
        if (arr[index].second == 'b') {
            *last_blue = index;
        }
    }
}
