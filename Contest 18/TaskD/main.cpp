#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "BigIntegerUtils2.h"

using std::cin;
using std::cout;
using std::string;
using std::vector;

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int64_t intern_days;
    string syrope_index;
    cin >> intern_days >> syrope_index;
    vector<int> arr_of_syrope_type(intern_days, 1);
    int curr = intern_days + 1;
    for (BigUnsigned type_of_syrope = stringToBigUnsigned(syrope_index) - 1; type_of_syrope > 0;
         type_of_syrope /= curr) {
        arr_of_syrope_type[--intern_days] = (type_of_syrope % --curr).toInt() + 1;
    }
    for (int i = 1; i <= arr_of_syrope_type.size(); ++i) {
        cout << arr_of_syrope_type[i - 1] << (i == arr_of_syrope_type.size() ? "" : " ");
    }
    return 0;
}
