#include <iostream>

using namespace std;

int main() {
    int n, k, m, z, count;
    cin >> n >> k >> m;
    z = k - (k % m);
    if (z != 0) {
        n = abs(n - k + z) - z;
        count = (n / z + 1) * (k / m);
        cout << count;
    } else {
        cout << 0;
    }
    return 0;
}
