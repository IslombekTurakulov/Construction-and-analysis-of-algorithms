#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <string>

using std::cin;
using std::cout;
using std::pair;
using std::string;
using std::vector;

vector<int64_t> component;

vector<vector<int64_t>> reverse(vector<vector<int64_t>> const &graph);

void firstDfs(vector<int64_t> *used, vector<vector<int64_t>> const &graph, int64_t node);

void secondDfs(vector<int64_t> *used, int64_t connection, vector<vector<int64_t>> const &graph,
               int64_t node);

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int64_t order_index = 0, order_size = INT64_MAX;
    int64_t data, clients, number_of_hours;
    cin >> data >> clients >> number_of_hours;
    vector<int64_t> arr_hours(data);
    vector<vector<int64_t>> graph(data);
    vector<pair<int64_t, int64_t>> data_centres(clients);
    for (int64_t index = 0; index < data; ++index) {
        cin >> arr_hours[index];
    }
    for (int64_t index = 0; index < clients; ++index) {
        cin >> data_centres[index].first >> data_centres[index].second;
        int64_t first = arr_hours[data_centres[index].first - 1] -
                        arr_hours[data_centres[index].second - 1] + number_of_hours;
        int64_t second = arr_hours[data_centres[index].second - 1] -
                         arr_hours[data_centres[index].first - 1] + number_of_hours;
        if (first % number_of_hours == 1) {
            graph[data_centres[index].second - 1].push_back(data_centres[index].first - 1);
        }
        if (second % number_of_hours == 1) {
            graph[data_centres[index].first - 1].push_back(data_centres[index].second - 1);
        }
    }
    int64_t size = static_cast<int64_t>(graph.size());
    vector<int64_t> used(size, 0);
    vector<vector<int64_t>> rev = reverse(graph);
    for (int64_t i = 0; i < size; ++i) {
        if (!used[i]) {
            firstDfs(&used, graph, i);
        }
    }
    used.assign(size, false);
    int64_t connections = 1;
    for (int64_t i = static_cast<int64_t>(component.size()) - 1; i > -1; --i) {
        if (!used[component[i]]) {
            secondDfs(&used, connections, rev, component[i]);
            ++connections;
        }
    }
    auto paired_ans = std::make_pair(used, connections - 1);
    int64_t length = paired_ans.second;
    vector<vector<int64_t>> new_arr(length);
    vector<int64_t> connections_array(length);
    vector<int64_t> order = paired_ans.first;
    for (int64_t index = 0; index < data; ++index) {
        ++connections_array[--order[index]];
    }
    for (int64_t i = 0; i < data; ++i) {
        for (int64_t j = 0; j < static_cast<int64_t>(graph[i].size()); ++j) {
            if (order[i] != order[graph[i][j]]) {
                new_arr[order[i]].push_back(order[graph[i][j]]);
            }
        }
    }
    for (int64_t index = 0; index < length; ++index) {
        if (new_arr[index].empty() && (connections_array[index] < order_size)) {
            order_index = index;
            order_size = connections_array[index];
        }
    }
    cout << order_size << "\n";
    for (int64_t index = 0; index < data; ++index) {
        if (order_index == order[index]) {
            cout << index + 1 << " ";
        }
    }
    return 0;
}

vector<vector<int64_t>> reverse(const vector<vector<int64_t>> &graph) {
    vector<vector<int64_t>> temp_arr(graph.size());
    for (int64_t i = 0; i < graph.size(); ++i) {
        for (int64_t j = 0; j < static_cast<int64_t>(graph[i].size()); ++j) {
            temp_arr[graph[i][j]].push_back(i);
        }
    }
    return temp_arr;
}

void firstDfs(vector<int64_t> *used, const vector<vector<int64_t>> &graph, int64_t node) {
    (*used)[node] = 1;
    for (int64_t i = 0; i < static_cast<int64_t>(graph[node].size()); ++i) {
        if ((*used)[graph[node][i]] == 0) {
            firstDfs(used, graph, graph[node][i]);
        }
    }
    component.push_back(node);
}

void secondDfs(vector<int64_t> *used, int64_t connection, const vector<vector<int64_t>> &graph,
               int64_t node) {
    (*used)[node] = connection;
    for (int64_t i = 0; i < static_cast<int64_t>(graph[node].size()); ++i) {
        if (!(*used)[graph[node][i]]) {
            secondDfs(used, connection, graph, graph[node][i]);
        }
    }
}
