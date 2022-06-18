#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::string;
using std::vector;

vector<bool> used;
vector<int> order;

void dfs(int connection, vector<vector<int>> const &graph);

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int clothes, connections;
    cin >> clothes >> connections;
    vector<string> names(clothes);
    vector<vector<int>> graph(clothes);
    vector<int> parents;
    used.assign(clothes, false);
    vector<bool> is_parent(clothes, true);
    for (int i = 0; i < clothes; ++i) {
        int num;
        cin >> num;
        getline(cin, names[i], '\n');
    }
    for (int i = 0; i < connections; ++i) {
        int first, second;
        cin >> first >> second;
        graph[first - 1].push_back(second - 1);
        is_parent[second - 1] = false;
    }
    for (int i = 0; i < clothes; ++i) {
        if (is_parent[i]) {
            parents.push_back(i);
        }
    }
    for (int i = 0; i < clothes; ++i) {
        sort(graph[i].begin(), graph[i].end(),
             [&](int const &x, int const &y) { return names[x] < names[y]; });
    }
    sort(parents.begin(), parents.end(),
         [&](int const &x, int const &y) { return names[x] < names[y]; });
    for (int parent : parents) {
        dfs(parent, graph);
    }
    for (int i = 0; i < clothes; ++i) {
        cout << names[order[clothes - 1 - i]] << "\n";
    }
    return 0;
}

void dfs(int connection, const vector<vector<int>> &graph) {
    used[connection] = 1;
    for (int node : graph[connection]) {
        if (!used[node]) {
            dfs(node, graph);
        }
    }
    order.push_back(connection);
}
