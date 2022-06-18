#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using std::cin;
using std::cout;
using std::pair;
using std::vector;

int checker(int students, int teams, int team, int middle, const vector<int> &groups);

pair<int, int> findTheMiddle(int team, int middle, int iteration, int amounts, int index);

pair<int, pair<int, int>> searchTheIndex(int middle, int amounts, int left, int right, int min);

int binSearch(int st, int teams, int temp, const vector<int> &vec, int left, int right, int min);

int main() {
    int students, teams, each_on_team;
    cin >> students >> teams >> each_on_team;
    vector<int> groups(students + 1);
    for (int i = 1; i <= students; ++i) {
        cin >> groups[i];
    }
    // В чатике разрешили использовать сортировку если есть бинарный поиск.
    // P.S: Aboba
    std::sort(groups.begin(), groups.end());
    if (students != each_on_team) {
        int left = 0;
        int right = groups[students] - groups[1];
        int min = right;
        cout << binSearch(students, teams, each_on_team, groups, left, right, min) << "\n";
    } else {
        cout << groups[students] - groups[1] << "\n";
    }
    return 0;
}

int binSearch(int st, int teams, int temp, const vector<int> &vec, int left, int right, int min) {
    while (left < right) {
        int middle = (left + right) / 2;
        int amounts = checker(st, teams, temp, middle, vec);
        auto result = searchTheIndex(middle, amounts, left, right, min);
        min = result.first;
        left = result.second.first;
        right = result.second.second;
    }
    return min;
}

pair<int, pair<int, int>> searchTheIndex(int middle, int amounts, int left, int right, int min) {
    if (amounts <= 0) {
        left = middle + 1;
    } else {
        if (middle < min) {
            min = middle;
        }
        right = middle;
    }
    return std::make_pair(min, std::make_pair(left, right));
}

int checker(int students, int teams, int team, int middle, const vector<int> &groups) {
    int amounts = 0;
    int index = 1;
    while (index <= students - team + 1) {
        int iteration = groups[index + team - 1] - groups[index];
        auto res = findTheMiddle(team, middle, iteration, amounts, index);
        amounts = res.first;
        index = res.second;
    }
    return amounts >= teams ? 1 : -1;
}

pair<int, int> findTheMiddle(int team, int middle, int iteration, int amounts, int index) {
    if (iteration > middle) {
        ++index;
    } else {
        index += team;
        ++amounts;
    }
    return std::make_pair(amounts, index);
}
