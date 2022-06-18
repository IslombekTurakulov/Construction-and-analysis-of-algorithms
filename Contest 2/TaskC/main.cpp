#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

int main() {
    int left = 0;
    int right = 10'000'001;
    int segments, to_count;
    cin >> segments >> to_count;
    int *array = new int[(segments)];
    for (int index = 0; index < segments; ++index) {
        cin >> array[index];
    }
    while (left + 1 < right) {
        int count = 0;
        int middle = (left + right) / 2;
        for (int index = 0; index < segments; ++index) {
            count += array[index] / middle;
        }
        count >= to_count ? left = middle : right = middle;
    }
    cout << left << "\n";
    delete[] array;
    return 0;
}
