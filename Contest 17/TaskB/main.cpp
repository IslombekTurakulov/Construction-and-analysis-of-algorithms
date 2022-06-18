#include "BigIntegerUtils2.h"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::string;
using std::vector;

BigInteger factorial(int n) {
    BigInteger fact_result = 1;
    for (int i = 2; i < n + 1; ++i) {
        fact_result *= i;
    }
    return fact_result;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int shirts, days;
    string position_plan;
    cin >> shirts >> days >> position_plan;
    vector<int> ans, arr(shirts);
    BigInteger k = stringToBigInteger(position_plan) - 1;
    std::iota(arr.begin(), arr.end(), 1);
    BigInteger alloc = factorial(shirts) / factorial(shirts - days);
    for (int i = days; i > 0; --i) {
        alloc /= shirts - days + i;
        int position = (k / alloc).toInt();
        ans.push_back(arr[position]);
        arr.erase(arr.begin() + position);
        k %= alloc;
    }
    for (int i = 0; i < days; ++i) {
        cout << ans[i] << (i + 1 == days ? "" : " ");
    }
    return 0;
}
