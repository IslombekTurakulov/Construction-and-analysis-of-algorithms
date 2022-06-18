// https://e-maxx.ru/algo/dfs
#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using std::cin;
using std::cout;
using std::getline;
using std::make_pair;
using std::pair;
using std::string;
using std::vector;

struct Vertex {
    string first;
    int second;
};

vector<bool> used;

void dfs(int owner_index, const vector<string> &invites, const vector<vector<int>> &sorted_invites,
         size_t *counter) {
    cout << invites[owner_index] << '\n';
    used[owner_index] = true;
    if (++(*counter) != invites.size()) {
        for (auto item : sorted_invites[owner_index]) {
            if (!used[item]) {
                dfs(item, invites, sorted_invites, counter);
            }
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int size, connections, owner_index;
    cin >> size;
    cin >> connections;
    if (size != 0) {
        vector<Vertex> invites(size);
        vector<string> people(size);
        vector<vector<int>> sorted_invites;
        for (int i = 0; i < size; ++i) {
            int first;
            string second;
            cin >> first;
            getline(cin, second);
            invites[i] = Vertex{.first = second, .second = i};
            people[i] = second;
        }
        std::sort(invites.begin(), invites.end(),
                  [](const Vertex &x, const Vertex &y) { return x.first < y.first; });
        vector<int> indexes(size);
        for (int i = 0; i < size; ++i) {
            indexes[invites[i].second] = i;
        }
        if (connections != 0) {
            sorted_invites.resize(size);
            for (int index = 0; index < connections; ++index) {
                int from, to;
                cin >> from >> to;
                sorted_invites[from].push_back(to);
                sorted_invites[to].push_back(from);
            }
            for (int i = 0; i < size; ++i) {
                std::sort(
                        sorted_invites[i].begin(), sorted_invites[i].end(),
                        [&indexes](int const &x, int const &y) { return indexes[x] < indexes[y]; });
            }
            used.resize(size, false);
            cin >> owner_index;
            size_t counter = 0;
            dfs(owner_index, people, sorted_invites, &counter);
        }
    }
    return 0;
}
