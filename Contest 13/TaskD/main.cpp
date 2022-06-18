#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <stack>
#include <utility>

using std::cin;
using std::cout;
using std::getline;
using std::make_pair;
using std::max;
using std::min;
using std::pair;
using std::queue;
using std::stack;
using std::string;
using std::vector;

void checkSteps(const vector<vector<int>>& table, stack<pair<int, int>>* points_save,
                const vector<pair<int, int>>& shifts, int current_step,
                stack<pair<int, int>>* queue);

void checkCoords(const int length, vector<vector<int>>* matrix, queue<pair<int, int>>* points,
                 stack<pair<int, int>>* used_steps, const vector<pair<int, int>>& horse_steps,
                 const pair<int, int>& current_steps);

void initialize(const int length, const pair<int, int>& coords_x, const pair<int, int>& coords_y) {
    vector<vector<int>> matrix(length + 1, vector<int>(length + 1, INT32_MAX));
    queue<pair<int, int>> steps;
    stack<pair<int, int>> used_steps;
    vector<pair<int, int>> horse_steps({make_pair(-2, -1), make_pair(-2, 1), make_pair(-1, -2),
                                        make_pair(-1, 2), make_pair(1, -2), make_pair(1, 2),
                                        make_pair(2, -1), make_pair(2, 1)});
    steps.push(coords_x);
    used_steps.push(coords_x);
    matrix.at(coords_x.first).at(coords_x.second) = 0;
    while (!steps.empty()) {
        auto current_steps = steps.front();
        steps.pop();
        if (current_steps.second == coords_y.second) {
            if (current_steps.first == coords_y.first) {
                stack<pair<int, int>> temp_que;
                cout << matrix.at(current_steps.first).at(current_steps.second) << "\n";
                int current_step = matrix.at(current_steps.first).at(current_steps.second);
                temp_que.push(current_steps);
                checkSteps(matrix, &used_steps, horse_steps, current_step, &temp_que);
                while (!temp_que.empty()) {
                    auto point_another = temp_que.top();
                    temp_que.pop();
                    cout << point_another.first << " " << point_another.second << "\n";
                }
                return;
            }
        }
        checkCoords(length, &matrix, &steps, &used_steps, horse_steps, current_steps);
    }
}

void checkCoords(const int length, vector<vector<int>>* matrix, queue<pair<int, int>>* points,
                 stack<pair<int, int>>* used_steps, const vector<pair<int, int>>& horse_steps,
                 const pair<int, int>& current_steps) {
    for (int index = 0; index < 8; ++index) {
        auto current_step = make_pair(current_steps.first + horse_steps.at(index).first,
                                      current_steps.second + horse_steps.at(index).second);
        if (current_step.first > 0 && current_step.first <= length && current_step.second > 0) {
            if (current_step.second <= length &&
                (*matrix).at(current_step.first).at(current_step.second) >
                    (*matrix).at(current_steps.first).at(current_steps.second) + 1) {
                (*matrix).at(current_step.first).at(current_step.second) =
                    (*matrix).at(current_steps.first).at(current_steps.second) + 1;
                (*points).push(current_step);
                (*used_steps).push(current_step);
            }
        }
    }
}

void checkSteps(const vector<vector<int>>& table, stack<pair<int, int>>* points_save,
                const vector<pair<int, int>>& shifts, int current_step,
                stack<pair<int, int>>* queue) {
    while (!(*points_save).empty()) {
        auto point_another = (*points_save).top();
        (*points_save).pop();
        auto step = table.at(point_another.first).at(point_another.second);
        if (step < current_step) {
            for (int point = 0; point < 8; ++point) {
                if ((*queue).top().first + shifts.at(point).first == point_another.first &&
                    (*queue).top().second + shifts.at(point).second == point_another.second) {
                    current_step = step;
                    (*queue).push(point_another);
                }
            }
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int length;
    cin >> length;
    pair<int, int> coord_x;
    pair<int, int> coord_y;
    cin >> coord_x.first >> coord_x.second >> coord_y.first >> coord_y.second;
    initialize(length, coord_x, coord_y);
    return 0;
}
