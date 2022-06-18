#include <iostream>
#include <queue>
#include <string>
#include <algorithm>
#include <vector>

using std::cin;
using std::cout;
using std::queue;
using std::string;
using std::vector;

bool bfs(const vector<vector<int>> &graph, int visible, int start, int temp, vector<int> *parent) {
    vector<bool> visited(visible, false);
    queue<int> queue;
    queue.push(start);
    visited[start] = true;
    (*parent)[start] = -1;
    while (!queue.empty()) {
        int front = queue.front();
        queue.pop();
        for (int i = 0; i < visible; ++i) {
            if (!visited[i] && graph.at(front).at(i) > 0) {
                if (visible != front) {
                    queue.push(i);
                    (*parent)[i] = front;
                    visited[i] = true;
                } else {
                    (*parent)[visible] = front;
                    return true;
                }
            }
        }
    }
    return visited.at(temp);
}

int fordFulkerson(vector<vector<int>> *graph, int visitor, int start, int temp) {
    vector<int> parent(visitor);
    int flow = 0;
    while (bfs(*graph, visitor, start, temp, &parent)) {
        int path = INT32_MAX;
        for (int i = temp; i != start; i = parent[i]) {
            path = std::min(path, graph->at(parent[i]).at(i));
        }
        for (int i = temp; i != start; i = parent[i]) {
            graph->at(parent[i]).at(i) -= path;
            graph->at(i).at(parent[i]) += path;
        }
        flow += path;
    }
    return flow;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n, vector<int>(n, 0));
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        graph.at(a - 1).at(b - 1) = c;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << graph[i][j] << " ";
        }
        cout << "\n";
    }
    cout << fordFulkerson(&graph, n, 0, n - 1) << "\n";
    return 0;
}
