#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::max_element;
using std::min_element;
using std::vector;

int main() {
    int length;
    int64_t index = 0;
    cin >> length;
    vector<int64_t> first(length);
    for (int64_t i = 0; i < length; ++i) {
        cin >> first[i];
    }
    auto max_length = *max_element(first.begin(), first.end());
    vector<int64_t> second(max_length + 1, 0);
    for (int64_t iteration: first) {
        ++second[iteration];
    }
    for (int64_t index_iter = 0; index_iter < second.size(); ++index_iter) {
        for (int64_t iteration = 0; iteration < second[index_iter]; ++iteration) {
            first[index] = index_iter;
            ++index;
        }
    }
    for (int64_t iteration = 0; iteration < length; ++iteration) {
        cout << first[iteration] << " ";
    }
    return 0;
}
