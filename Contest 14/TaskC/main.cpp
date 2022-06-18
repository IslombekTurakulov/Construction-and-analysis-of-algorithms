#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

using std::cin;
using std::cout;
using std::set;
using std::string;
using std::vector;

vector<int> component;

void firstDfs(vector<vector<int>> const &graph, vector<int> *used, int node);

void secondDfs(vector<vector<int>> const &graph, vector<int> *used, int connections, int node);

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int vertices, edges;
    vector<set<string>> connection_clothes;
    cin >> vertices >> edges;
    vector<vector<int>> graph(vertices);
    vector<string> clothes(vertices);
    for (int index = 0; index < vertices; ++index) {
        int num;
        cin >> num;
        getline(cin, clothes[index]);
    }
    vector<vector<int>> rev(vertices);
    for (int i = 0; i < edges; ++i) {
        int first, second;
        cin >> first >> second;
        graph[first].push_back(second);
        rev[second].push_back(first);
    }
    vector<int> used(graph.size());
    for (int i = 0; i < graph.size(); ++i) {
        if (used[i] == 0) {
            firstDfs(graph, &used, i);
        }
    }
    used.assign(graph.size(), false);
    int connections = 1;
    for (int i = component.size() - 1; i >= 0; --i) {
        if (used[component[i]] == 0) {
            secondDfs(rev, &used, connections, component[i]);
            ++connections;
        }
        if (connection_clothes.size() < used[component[i]]) {
            connection_clothes.resize(used[component[i]]);
        }
        connection_clothes[used[component[i]] - 1].insert(clothes[component[i]]);
    }
    sort(connection_clothes.begin(), connection_clothes.end());
    for (const auto &item : connection_clothes) {
        for (const auto &name : item) {
            cout << name << "\n";
        }
        cout << "\n";
    }
}

void secondDfs(const vector<vector<int>> &graph, vector<int> *used, int connections, int node) {
    (*used)[node] = connections;
    for (int i = 0; i < static_cast<int>(graph[node].size()); ++i) {
        if ((*used)[graph[node][i]] == 0) {
            secondDfs(graph, used, connections, graph[node][i]);
        }
    }
}

void firstDfs(const vector<vector<int>> &graph, vector<int> *used, int node) {
    (*used)[node] = 1;
    for (int i = 0; i < static_cast<int>(graph[node].size()); ++i) {
        if ((*used)[graph[node][i]] == 0) {
            firstDfs(graph, used, graph[node][i]);
        }
    }
    component.push_back(node);
}
