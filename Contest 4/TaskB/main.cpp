#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::max_element;
using std::vector;

int main() {
    int64_t length;
    int64_t offset = 1;
    cin >> length;
    vector<int64_t> array(length);
    vector<int64_t> second(length * 4);
    for (int64_t i = 0; i < length; ++i) {
        cin >> array[i];
    }
    int64_t max = *max_element(array.begin(), array.end());
    for (; max / offset > 0;) {
        int base = 256;
        vector<int64_t> temp(base, 0);
        int64_t iteration;
        for (iteration = 0; iteration < length; ++iteration) {
            ++temp[array[iteration] / offset % base];
        }
        for (iteration = 1; iteration < base; ++iteration) {
            temp[iteration] += temp[iteration - 1];
        }
        for (iteration = length - 1; iteration >= 0; --iteration) {
            second[--temp[array[iteration] / offset % base]] = array[iteration];
        }
        for (iteration = 0; iteration < length; ++iteration) {
            array[iteration] = second[iteration];
        }
        offset *= base;
    }
    for (int64_t i = 0; i < length; ++i) {
        cout << array[i] << " ";
    }
    return 0;
}
