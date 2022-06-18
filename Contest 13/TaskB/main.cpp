// https://e-maxx.ru/algo/bfs
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>

using std::cin;
using std::cout;
using std::getline;
using std::queue;
using std::string;
using std::vector;

vector<int> bfs(int size, int owner_index, const vector<vector<int>>& sorted_invites);

void showResults(std::map<int, vector<string>>* sorted_guests);

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int size, connections, owner_index;
    cin >> size;
    cin >> connections;
    if (size != 0) {
        vector<string> invites(size);
        vector<vector<int>> sorted_invites;
        for (int i = 0; i < size; ++i) {
            int first;
            string second;
            cin >> first;
            getline(cin, second);
            invites[i] = second;
        }
        if (connections != 0) {
            sorted_invites.resize(size);
            for (int index = 0; index < connections; ++index) {
                int from, to;
                cin >> from >> to;
                sorted_invites[from].push_back(to);
                sorted_invites[to].push_back(from);
            }
            cin >> owner_index;
            vector<int> d_arr = bfs(size, owner_index, sorted_invites);
            std::map<int, vector<string>> sorted_guests;
            for (int i = 0; i < size; ++i) {
                sorted_guests[d_arr[i]].push_back(invites[i]);
            }
            showResults(&sorted_guests);
        }
    }
    return 0;
}

void showResults(std::map<int, vector<string>>* sorted_guests) {
    for (auto obj : (*sorted_guests)) {
        std::sort(obj.second.begin(), obj.second.end());
        for (const auto& item : obj.second) {
            cout << item << "\n";
        }
    }
}

vector<int> bfs(int size, int owner_index, const vector<vector<int>>& sorted_invites) {
    queue<int> q_arr;
    vector<int> d_arr(size, -1);
    vector<int> p_arr(size);
    q_arr.push(owner_index);
    d_arr[owner_index] = 0;
    while (!q_arr.empty()) {
        int num = q_arr.front();
        q_arr.pop();
        for (int value : sorted_invites[num]) {
            if (d_arr[value] == -1) {
                q_arr.push(value);
                d_arr[value] = d_arr[num] + 1;
                p_arr[value] = num;
            }
        }
    }
    return d_arr;
}
