#include <iostream>
#include "BigIntegerUtils2.h"
#include <string>

using std::cin;
using std::cout;
using std::string;

BigInteger pathFinder(int rows, int columns) {
    if (rows < 1 || columns < 1) {
        return -1;
    }
    if (rows == 1 && columns == 1) {
        return 0;
    }
    if (rows == 1 || columns == 1) {
        return 1;
    }
    BigInteger **paths = new BigInteger *[rows];
    // O(n)
    for (int i = 0; i < rows; ++i) {
        paths[i] = new BigInteger[columns];
    }
    // O(n^2)
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            paths[i][j] = j == 0 || i == rows - 1 ? 1 : 0;
        }
    }
    // O(n^2)
    for (int i = rows - 2; i >= 0; --i) {
        for (int j = 1; j < columns; ++j) {
            paths[i][j] = paths[i + 1][j] + paths[i][j - 1];
        }
    }
    BigInteger result = paths[0][columns - 1];
    for (int i = 0; i < rows; ++i) {
        delete[] paths[i];
    }
    delete[] paths;
    return result;
}

int main() {
    int lines = 0;
    int columns = 0;
    cin >> lines >> columns;
    BigInteger count = pathFinder(lines + 1, columns + 1);
    cout << bigIntegerToString(count);
    return 0;
}
