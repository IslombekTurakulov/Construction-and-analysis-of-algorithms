#include "BigIntegerUtils2.h"
#include <iostream>
#include <set>
#include <string>

using std::cin;
using std::cout;
using std::set;
using std::string;
using std::to_string;

BigInteger findFirstNumIndex(BigInteger *position, int size) {
    if (size == 1) {
        return 0;
    }
    size--;
    BigInteger temp_size = size;
    while ((*position) >= temp_size && size > 1) {
        temp_size = temp_size * (size - 1);
        size--;
    }
    BigInteger index = (*position) / temp_size;
    (*position) = (*position) % temp_size;
    return index;
}

string findKthPermutation(int n, BigInteger position) {
    string result;
    set<BigInteger> stack_of_nums;
    for (int i = 1; i <= n; ++i) {
        stack_of_nums.insert(i);
    }
    set<BigInteger>::iterator itr;
    itr = stack_of_nums.begin();
    position = position - 1;
    for (int i = 0; i < n; ++i) {
        BigInteger index = findFirstNumIndex(&position, n - i);
        advance(itr, index.toUnsignedLong());
        result += (i + 1 >= n ? bigIntegerToString(*itr) : bigIntegerToString(*itr) + " ");
        stack_of_nums.erase(itr);
        itr = stack_of_nums.begin();
    }
    return result;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    string k;
    cin >> n >> k;
    string kth_perm_seq = findKthPermutation(n, stringToBigInteger(k));
    cout << kth_perm_seq;
    return 0;
}
