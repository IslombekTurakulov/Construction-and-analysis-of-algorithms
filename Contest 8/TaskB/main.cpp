#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::string;
using std::vector;

vector<int> zFunction(const string& s) {
    size_t n = s.size();
    vector<int> z(n);
    z[0] = 0;
    int left = 0;
    int right = 0;
    for (int i = 1; i < n; ++i) {
        if (i <= right) {
            z[i] = std::min(right - i + 1, z[i - left]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] - 1 > right) {
            left = i;
            right = i + z[i] - 1;
        }
    }
    return z;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    string s;
    cin >> s;
    auto res = zFunction(s);
    int index;
    for (int i = 0; i < res.size(); ++i) {
        cout << res.at(i);
    }
    cout << "\n";
    for (index = 0; index < res.size(); ++index) {
        if (res[index] == res.size() - index) {
            break;
        }
    }
    std::cout << index << '\n';
    return 0;
}