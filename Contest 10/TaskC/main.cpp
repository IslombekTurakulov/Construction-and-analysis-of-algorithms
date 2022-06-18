#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int len;
    int counter = 0;
    int index = 1;
    string input;
    cin >> len;
    cin >> input;
    int *arr = new int[len];
    arr[0] = input[0] - '0';
    for (; index < len; ++index) {
        arr[index] = arr[index - 1] + input[index] - '0';
    }
    index = 1;
    for (; index < len; ++index) {
        bool flag = false;
        for (int i = index; i < len; i += index + 1) {
            if (arr[i] % 2) {
                flag = true;
                break;
            }
        }
        if (!flag) {
            ++counter;
        }
    }
    cout << counter;
    delete[] arr;
    return 0;
}
