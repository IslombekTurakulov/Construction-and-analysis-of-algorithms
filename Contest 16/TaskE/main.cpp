// https://e-maxx.ru/algo/dinic
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <string>

using std::cin;
using std::cout;
using std::map;
using std::string;
using std::vector;

const int64_t kMax = 500000;
const int64_t kInf = 1e16;

struct Edge {
    int64_t from, to, capacity, flow;
};

int64_t n, m, requests, start, position_to_direct;
vector<int64_t> visited_arr(kMax);
vector<int64_t> arr_pointers(kMax);
vector<int64_t> stack_arr(kMax);
vector<int64_t> graph[kMax];
vector<Edge> array_of_edges;

void addEdge(int64_t from, int64_t to, int64_t cap) {
    graph[from].push_back(static_cast<int64_t>(array_of_edges.size()));
    array_of_edges.push_back({from, to, cap, 0});
    graph[to].push_back(array_of_edges.size());
    array_of_edges.push_back({to, from, cap, 0});
}

bool bfs() {
    int64_t left = 0, right = 0;
    stack_arr[right++] = start;
    visited_arr.assign(n, -1);
    visited_arr[start] = 0;
    while (left < right && visited_arr[position_to_direct] == -1) {
        int64_t number = stack_arr[left++];
        for (size_t i = 0; i < graph[number].size(); ++i) {
            int64_t index = graph[number][i], to = array_of_edges[index].to;
            if (visited_arr[to] == -1 &&
                array_of_edges[index].flow < array_of_edges[index].capacity) {
                stack_arr[right++] = to;
                visited_arr[to] = visited_arr[number] + 1;
            }
        }
    }
    return visited_arr[position_to_direct] != -1;
}

int64_t dfs(int64_t direction, int64_t flow) {
    if (flow != 0) {
        if (direction != position_to_direct) {
            for (; arr_pointers[direction] < static_cast<int64_t>(graph[direction].size());
                 ++arr_pointers[direction]) {
                int64_t id = graph[direction][arr_pointers[direction]], to = array_of_edges[id].to;
                if (visited_arr[to] != visited_arr[direction] + 1) {
                    continue;
                }
                int64_t pushed =
                    dfs(to, std::min(flow, array_of_edges[id].capacity - array_of_edges[id].flow));
                if (pushed) {
                    array_of_edges[id].flow += pushed;
                    array_of_edges[id ^ 1].flow -= pushed;
                    return pushed;
                }
            }
        } else {
            return flow;
        }
    }
    return 0;
}

int64_t dinicMethod() {
    int64_t flow = 0;
    bool flag = true;
    while (flag) {
        if (bfs()) {
            arr_pointers.assign(n, 0);
            while (int64_t pushed = dfs(start, kInf)) {
                flow += pushed;
            }
        } else {
            flag = false;
        }
    }
    return flow;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    std::cin >> n >> m >> requests;
    n++;
    std::map<std::string, int64_t> map;
    int64_t counter = 1;
    for (int64_t index_first = 0; index_first < m; ++index_first) {
        std::string first;
        std::string second;
        cin >> first >> second;
        if (!map[first]) {
            map[first] = counter++;
        }
        if (!map[second]) {
            map[second] = counter++;
        }
        if (map[first] != map[second]) {
            addEdge(map[first], map[second], 1);
        }
    }

    for (int index_second = 0; index_second < requests; ++index_second) {
        string first;
        string second;
        cin >> first >> second;
        if (first != second) {
            start = map[first];
            position_to_direct = map[second];
            visited_arr.assign(n, 0);
            arr_pointers.assign(n, 0);
            stack_arr.assign(n, 0);
            for (int64_t j = 0; j < array_of_edges.size(); ++j) {
                array_of_edges[j].flow = 0;
            }
            cout << dinicMethod() << "\n";
        } else {
            cout << 0 << "\n";
        }
    }
    return 0;
}
