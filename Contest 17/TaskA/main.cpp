#include "BigIntegerUtils2.h"
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

BigInteger factorialNum(bool is_even, int n) {
    BigInteger big_integer = (stringToBigInteger(std::to_string(1)));
    for (int i = 2; i < n + 1; ++i) {
        if (i % 2 || is_even) {
            big_integer *= stringToBigInteger(std::to_string(i));
        }
    }
    return big_integer;
}

BigInteger factorial(int n, BigInteger integer) {
    // BigInteger big_integer = BigInteger(1);
    for (int i = 1; i < n; ++i) {
        integer *= stringToBigInteger(std::to_string(i));
    }
    return integer;
}

BigInteger recurValid(int n, int k) {
    return factorial(n, stringToBigInteger(std::to_string(n))) /
           (factorial(k, stringToBigInteger(std::to_string(k))) *
            factorial(n - k, stringToBigInteger(std::to_string(n - k))));
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, k;
    cin >> n >> k;
    cout << factorialNum(true, n) << "\n";
    cout << recurValid(n, k) << "\n";
    cout << factorialNum(false, n) << "\n";
    return 0;
}
