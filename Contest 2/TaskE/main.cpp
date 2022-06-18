#include <iostream>
#include <cmath>
#include <iomanip>

double getFunc(double middle);

using std::cin;
using std::cout;

int main() {
    double eps = 1e-10;
    double input;
    cin >> input;
    double left = 0, right = input;
    while (right - left > eps) {
        double middle = (left + right) / 2;
        if (getFunc(middle) > input) {
            right = middle;
        } else {
            left = middle;
        }
    }

    cout << std::fixed << std::setprecision(9) << left;

    return 0;
}

double getFunc(double middle) {
    return middle * middle + sqrt(middle);
}
