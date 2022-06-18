// https://www.cs.princeton.edu/courses/archive/spr05/cos423/lectures/06dynamic-programming.pdf
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::string;
using std::vector;

struct Interval {
    double start;
    double end;
    double weight;
};

int findInterval(vector<Interval> const &array, int curr_index) {
    int left = 0;
    int right = curr_index;
    while (left <= right) {
        int middle = (left + right) / 2;
        if (array[curr_index].start >= array[middle].end) {
            if (array[curr_index].start >= array[middle + 1].end) {
                left = middle + 1;
            } else {
                return middle;
            }
        } else {
            right = middle - 1;
        }
    }
    return -1;
}

double findSolution(vector<Interval> array, double *weight_max_result) {
    weight_max_result[0] = array[0].weight;
    for (int index = 1; index < static_cast<int>(array.size()); ++index) {
        double weight = array[index].weight;
        int curr_interval = findInterval(array, index);
        if (curr_interval != -1) {
            weight += weight_max_result[curr_interval];
        }
        weight_max_result[index] = std::max(weight, weight_max_result[index - 1]);
    }
    return weight_max_result[array.size() - 1];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int length;
    cin >> length;
    vector<Interval> array(length);
    double *weight_max_result = new double[length];
    for (int i = 0; i < length; ++i) {
        double start, end, weight;
        cin >> start;
        cin >> end;
        cin >> weight;
        array[i] = {.start = start, .end = end, .weight = weight};
    }
    std::sort(array.begin(), array.end(), [](Interval &x, Interval &y) { return x.end < y.end; });
    cout << std::fixed;
    cout.precision(4);
    cout << (array.empty() ? 0 : findSolution(array, weight_max_result));
    delete[] weight_max_result;
    return 0;
}
