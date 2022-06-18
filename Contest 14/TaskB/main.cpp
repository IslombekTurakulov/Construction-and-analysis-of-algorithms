#include <iostream>
#include <unordered_set>
#include <vector>

using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::unordered_set;

vector<vector<int>> graph;
vector<vector<int>> reversed_graph;
vector<unordered_set<int>> sorted_graph;
vector<unordered_set<int>> edges;
vector<int> ordered;
vector<int> order;
vector<int> array_of_vertices;
vector<int> component;
int color = 0;
int number_of_edges;

void firstDfs(int curr);

void secondDfs(int curr);

void secondRes(int curr);

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int vertices, first, second;
    cin >> vertices >> number_of_edges;
    reversed_graph = vector<vector<int>>(vertices);
    array_of_vertices = vector<int>(vertices);
    graph = vector<vector<int>>(vertices);
    for (int i = 0; i < number_of_edges; ++i) {
        cin >> first >> second;
        graph[first - 1].push_back(second - 1);
        reversed_graph[second - 1].push_back(first - 1);
    }
    // First
    for (int i = 0; i < static_cast<int>(graph.size()); ++i) {
        if (!array_of_vertices[i]) {
            firstDfs(i);
        }
    }
    array_of_vertices = vector<int>(graph.size(), 0);
    for (int index = static_cast<int>(graph.size()) - 1; index > -1; --index) {
        if (!array_of_vertices[ordered[index]]) {
            secondDfs(ordered[index]);
            ++color;
            if (order.size() > 1) {
                for (int j = 1; j < static_cast<int>(order.size()); ++j) {
                    component.push_back(order[j - 1]);
                    component.push_back(order[j]);
                }
                component.push_back(order.back());
                component.push_back(order.front());
            }
            order.clear();
        }
    }
    ++color;
    sorted_graph = vector<unordered_set<int>>(color);
    edges = vector<unordered_set<int>>(color);
    for (int index = 0; index < static_cast<int>(graph.size()); ++index) {
        for (int child : graph[index]) {
            if (array_of_vertices[index] != array_of_vertices[child]) {
                sorted_graph[array_of_vertices[index]].insert(array_of_vertices[child]);
            }
        }
    }
    // Second
    order = vector<int>(color);
    for (int index = 1; index < color; ++index) {
        if (!order[index]) {
            secondRes(index);
        }
    }
    for (int index = 0; index < static_cast<int>(graph.size()); ++index) {
        for (int child : graph[index]) {
            if (sorted_graph[array_of_vertices[index]].count(array_of_vertices[child])) {
                component.push_back(index);
                component.push_back(child);
                sorted_graph[array_of_vertices[index]].erase(array_of_vertices[child]);
            }
        }
    }
    cout << component.size() / 2 << "\n";
    for (int road : component) {
        cout << road + 1 << " ";
    }
    return 0;
}

void secondDfs(int curr) {
    array_of_vertices[curr] = color;
    order.push_back(curr);
    for (int node : reversed_graph[curr]) {
        if (!array_of_vertices[node]) {
            secondDfs(node);
        }
    }
}

void firstDfs(int curr) {
    array_of_vertices[curr] = 1;
    for (int node : graph[curr]) {
        if (!array_of_vertices[node]) {
            firstDfs(node);
        }
    }
    ordered.push_back(curr);
}

void secondRes(int curr) {
    order[curr] = 1;
    vector<int> arr;
    for (int node : sorted_graph[curr]) {
        edges[curr].insert(node);
        if (!order[node]) {
            secondRes(node);
        }
        for (int other : edges[node]) {
            if (!sorted_graph[curr].count(other)) {
                edges[curr].insert(other);
            } else {
                arr.push_back(other);
            }
        }
    }
    for (int node : arr) {
        sorted_graph[curr].erase(node);
    }
}
