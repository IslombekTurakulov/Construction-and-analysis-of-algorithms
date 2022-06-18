#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <utility>

using std::abs;
using std::cin;
using std::cout;
using std::make_pair;
using std::pair;
using std::set;
using std::string;
using std::to_string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

int getDigit(int num);

void subExtra(int num, unordered_set<int> *ans);

void subExtraSecond(int num, unordered_set<int> *ans);

void subOneDigit(int num, unordered_set<int> *ans);

void subTwoDigits(int num, unordered_set<int> *ans);

void subThreeDigits(int num, unordered_set<int> *ans);

void subFourDigits(int num, unordered_set<int> *ans);

unordered_set<int> getSubNumbers(int num) {
    unordered_set<int> result;
    if (to_string(num).length() > 3) {
        subFourDigits(num, &result);
    } else if (to_string(num).length() > 2) {
        subThreeDigits(num, &result);
    } else if (to_string(num).length() > 1) {
        subTwoDigits(num, &result);
    } else if (num > 0) {
        subOneDigit(num, &result);
    }
    return result;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    set<pair<int, int>> ways;
    int n, a, b;
    cin >> n >> a >> b;
    vector<unordered_map<int, int>> graph(n + 1);
    vector<int> dists(n + 1, INT32_MAX);
    dists[a] = 0;
    vector<int> history(n + 1, -1);
    ways.insert(make_pair(dists[a], a));
    for (int index = 1; index < n + 1; ++index) {
        for (auto num : getSubNumbers(index)) {
            if (index - num > 0) {
                graph[index][index - num] = getDigit(num);
            }
            if (index + num < n + 1) {
                graph[index][index + num] = getDigit(num);
            }
        }
    }
    while (!ways.empty()) {
        int index = ways.begin()->second;
        ways.erase(ways.begin());
        for (auto const &item : graph[index]) {
            if (dists[index] + item.second < dists[item.first]) {
                ways.erase(make_pair(dists[item.first], item.first));
                ways.insert(make_pair(dists[index] + item.second, item.first));
                dists[item.first] = dists[index] + item.second;
                history[item.first] = index;
            }
        }
    }
    if (dists[b] != INT32_MAX) {
        int index = b, cost = 0, length = 0;
        vector<string> temp_vec;
        while (history[index] != -1) {
            cost += getDigit(abs(index - history[index]));
            temp_vec.push_back(index - history[index] > 0 ? '+' + to_string(index - history[index])
                                                          : to_string(index - history[index]));
            index = history[index];
            ++length;
        }
        cout << cost << "\n" << length << "\n";
        for (index = temp_vec.size() - 1; index >= 0; --index) {
            cout << temp_vec[index] << "\n";
        }
    } else {
        cout << -1 << "\n";
    }
    return 0;
}

int getDigit(int num) {
    int res = 0;
    while (num > 0) {
        res += num % 10;
        num /= 10;
    }
    return res;
}

void subOneDigit(int num, unordered_set<int> *ans) {
    ans->insert(num % 10);
}

void subTwoDigits(int num, unordered_set<int> *ans) {
    ans->insert(num % 100);
    subExtra(num, ans);
}

void subThreeDigits(int num, unordered_set<int> *ans) {
    ans->insert(num % 1000);
    subExtraSecond(num, ans);
    ans->insert(num / 100 % 10);
    subExtra(num, ans);
}

void subFourDigits(int num, unordered_set<int> *ans) {
    ans->insert(num % 10000);
    ans->insert(num % 1000);
    ans->insert(num / 10 % 1000);
    subExtraSecond(num, ans);
    ans->insert(num / 1000 % 10);
    ans->insert(num / 100 % 10);
    subExtra(num, ans);
}

void subExtra(int num, unordered_set<int> *ans) {
    ans->insert(num / 10 % 10);
    ans->insert(num % 10);
}

void subExtraSecond(int num, unordered_set<int> *ans) {
    ans->insert(num / 100);
    ans->insert(num / 10 % 100);
    ans->insert(num % 100);
}
