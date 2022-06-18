#include <iostream>
#include <queue>
#include <vector>

using std::cin;
using std::cout;
using std::queue;
using std::vector;

struct Direction {
    int child;
    int network;
    int connection;
};

vector<vector<int>> graph;
vector<int> distances;
vector<int> children;
vector<Direction> edges;
int initial = 0;
int edge = 0;
int cost;
int64_t sum;

void addEdge(const int &node, const int &child, const int &connection);

bool bfs();

bool dfs(const int node);

int main() {
    int rows, columns;
    int white_cost, black_cost, gray_line;
    int64_t flows = 0;
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> rows >> columns >> white_cost >> black_cost >> gray_line;
    graph.resize(rows * columns + 2);
    edges.resize((rows * columns + 2) * 6);
    cost = rows * columns + 1;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            char color_symbol;
            cin >> color_symbol;
            int node_index = i * columns + j + 1;
            if (color_symbol == 'W') {
                addEdge(initial, node_index, black_cost);
            } else {
                addEdge(node_index, cost, white_cost);
            }
        }
    }
    for (int index = 0; index < rows; ++index) {
        for (int j = 0; j < columns; ++j) {
            int node = index * columns + j + 1;
            if (j + 1 < columns) {
                addEdge(node, node + 1, gray_line);
                edges[edge - 1].connection = 0;
            }
            if (index + 1 < rows) {
                addEdge(node, (index + 1) * columns + j + 1, gray_line);
                edges[edge - 1].connection = 0;
            }
        }
    }
    sum = (1 << 30);
    while (sum) {
        if (bfs()) {
            children.assign(graph.size(), 0);
            while (dfs(initial)) {
                flows += sum;
            }
        } else {
            sum >>= 1;
        }
    }
    cout << flows << "\n";
    return 0;
}

void addEdge(const int &node, const int &child, const int &connection) {
    int bit_conversion = edge ^ 1;
    edges[edge].child = child;
    edges[edge].connection = 0;
    edges[bit_conversion].child = node;
    edges[bit_conversion].connection = edges[bit_conversion].network = edges[edge].network =
        connection;
    graph[node].push_back(edge);
    graph[child].push_back(bit_conversion);
    edge += 2;
}

bool bfs() {
    queue<int> queue;
    queue.push(initial);
    distances.assign(graph.size(), INT32_MAX);
    distances[initial] = 0;
    while (!queue.empty() && distances[cost] == INT32_MAX) {
        int node = queue.front();
        queue.pop();
        for (int i = 0; i < graph[node].size(); ++i) {
            if (distances[edges[graph[node][i]].child] == INT32_MAX &&
                edges[graph[node][i]].network - edges[graph[node][i]].connection >= sum) {
                distances[edges[graph[node][i]].child] = distances[node] + 1;
                queue.push(edges[graph[node][i]].child);
            }
        }
    }
    return distances[cost] != INT32_MAX;
}

bool dfs(const int node) {
    while (children[node] < graph[node].size()) {
        int child = edges[graph[node][children[node]]].child;
        if (distances[child] == distances[node] + 1 &&
            edges[graph[node][children[node]]].network -
                    edges[graph[node][children[node]]].connection >=
                sum &&
            (child == cost || dfs(child))) {
            edges[graph[node][children[node]]].connection += sum;
            edges[graph[node][children[node]] ^ 1].connection -= sum;
            return true;
        }
        ++children[node];
    }
    return false;
}
