#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::min;
using std::string;
using std::vector;

struct Directions {
    int64_t from;
    int64_t to;
    int64_t weight;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int64_t vertices, edges;
    cin >> vertices >> edges;
    vector<vector<Directions>> graph(vertices, vector<Directions>(vertices, {0, 0, INT64_MAX}));
    for (int64_t i = 0; i < edges; ++i) {
        int64_t from, to, weight;
        cin >> from >> to >> weight;
        graph[from][to] = {from, to, weight};
    }
    for (int first = 0; first < vertices; ++first) {
        for (int64_t second = 0; second < vertices; ++second) {
            for (int third = 0; third < vertices; ++third) {
                if (graph[first][third].weight != INT64_MAX) {
                    if (graph[second][first].weight != INT64_MAX) {
                        graph[second][third].weight =
                            min(graph[second][third].weight,
                                graph[second][first].weight + graph[first][third].weight);
                    }
                }
            }
        }
    }
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            if (i != j) {
                cout << i << " " << j << " ";
                cout << (graph[i][j].weight != INT64_MAX ? graph[i][j].weight : -1) << "\n";
            }
        }
    }
    return 0;
}
