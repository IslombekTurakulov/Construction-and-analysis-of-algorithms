#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::max;
using std::min;
using std::string;
using std::vector;

struct Directions {
    int64_t from;
    int64_t to;
    int64_t cost;
};

int main() {
    int64_t vertices, edges;
    vector<Directions> array_of_edges;
    cin >> vertices >> edges;
    // cout << vertices - 1 << "\n";
    array_of_edges.resize(edges);
    vector<int64_t> dist(vertices, INT64_MAX);
    dist[0] = 0;
    for (int64_t i = 0; i < edges; ++i) {
        cin >> array_of_edges[i].from >> array_of_edges[i].to >> array_of_edges[i].cost;
    }
    for (int64_t first = 0; first < vertices - 1; ++first) {
        for (int64_t second = 0; second < edges; ++second) {
            // cout << second << "\n";
            int64_t from = array_of_edges[second].from;
            if (dist[from] < INT64_MAX) {
                int64_t cost = array_of_edges[second].cost;
                int64_t is_valid = dist[from] + cost;
                if (is_valid < dist[array_of_edges[second].to]) {
                    dist[array_of_edges[second].to] =
                        min(is_valid, dist[array_of_edges[second].to]);
                }
            }
        }
    }
    vector<int64_t> temp_second_arr = dist;
    for (int64_t first = 0; first < vertices - 1; ++first) {
        for (int64_t second = 0; second < edges; ++second) {
            // cout << second << "\n";
            int64_t from = array_of_edges[second].from;
            if (temp_second_arr[from] < INT64_MAX) {
                int64_t cost = array_of_edges[second].cost;
                int64_t is_valid = temp_second_arr[from] + cost;
                if (is_valid < temp_second_arr[array_of_edges[second].to]) {
                    temp_second_arr[array_of_edges[second].to] =
                        min(is_valid, temp_second_arr[array_of_edges[second].to]);
                }
            }
        }
    }
    for (int64_t k = 1; k < vertices; ++k) {
        if (temp_second_arr[k] != dist[k]) {
            dist[k] = -INT64_MAX;
        }
    }
    vector<int64_t> result(dist.size(), 1);
    for (int i = 1; i < result.size(); ++i) {
        if (dist[i] != temp_second_arr[i]) {
            result[i] = 0;
        }
    }

    for (int index = 0; index < result.size(); ++index) {
        for (int index_j = 0; index_j < array_of_edges.size(); ++index_j) {
            if (result[array_of_edges[index_j].from] == 0) {
                result[array_of_edges[index_j].to] = 0;
            }
        }
    }

    for (int i = 1; i < result.size(); ++i) {
        cout << (result[i] == 0 ? "-inf" : std::to_string(dist[i])) << "\n";
    }
    return 0;
}
