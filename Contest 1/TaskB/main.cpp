#include <iostream>
#include <stack>
#include <vector>

using std::cin;
using std::cout;
using std::stack;
using std::vector;

int64_t heightCalc(int64_t res, int64_t in, int64_t top, const stack<int64_t> &arr, int64_t len);

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int64_t res = 0;
    int64_t index = 0;
    int64_t length;
    int64_t top = 0;
    cin >> length;
    vector<int64_t> arr(length + 1);
    for (int64_t i = 0; i < length; ++i) {
        cin >> arr[i];
    }
    stack<int64_t> columns;
    while (index < length) {
        if (columns.empty() || arr[columns.top()] <= arr[index]) {
            columns.push(index);
            ++index;
        } else {
            int64_t element_from_height = arr.at(columns.top());
            columns.pop();
            res = heightCalc(res, index, top, columns, element_from_height);
        }
    }
    while (!columns.empty()) {
        int64_t element_from_height = arr.at(columns.top());
        columns.pop();
        res = heightCalc(res, index, top, columns, element_from_height);
    }
    cout << res << "\n";
    return 0;
}

int64_t heightCalc(int64_t res, int64_t in, int64_t top, const stack<int64_t> &arr, int64_t len) {
    if (arr.empty()) {
        top = len * in;
    } else {
        top = len * (in - arr.top() - 1);
    }
    if (res < top) {
        res = top;
    }
    return res;
}
