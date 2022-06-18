#include <iostream>

using std::cin;
using std::cout;

int lowerBound(int left, int right, int value);

int upperBound(int left, int right, int value);

int getInput(int left, int right);

int main() {
    int right = 0;
    int left = 1;
    cin >> right;
    int value = getInput(left, right);
    if (value != left) {
        int input = getInput(1, value);
        if (input == value) {
            right = value;
            left = lowerBound(left, right, value);
            cout << "! " << left;
        } else {
            left = value;
            right = upperBound(left, right, value);
            cout << "! " << right;
        }
    } else {
        left = value;
        right = upperBound(left, right, value);
        cout << "! " << right;
    }
    return 0;
}

int upperBound(int left, int right, int value) {
    while (left + 1 < right) {
        int mid = (left + right) / 2;
        getInput(value, mid) == value ? right = mid : left = mid;
    }
    return right;
}

int lowerBound(int left, int right, int value) {
    while (left + 1 < right) {
        int mid = (left + right) / 2;
        getInput(mid, value) == value ? left = mid : right = mid;
    }
    return left;
}

int getInput(int left, int right) {
    cout << "? " << left << " " << right << "\n";
    fflush(stdout);
    int input;
    cin >> input;
    return input;
}
