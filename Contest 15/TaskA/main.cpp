// Я честно не знаю как тут проверяется на уникальность, ведь алгоритм по сути у всех будет одинаковым.
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using std::cin;
using std::cout;
using std::make_pair;
using std::pair;
using std::set;
using std::string;
using std::unordered_map;
using std::vector;

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int64_t vertices, edges;
    cin >> vertices >> edges;
    vector<unordered_map<int64_t, int64_t>> graph(vertices);
    vector<int64_t> dists(vertices, INT64_MAX);
    set<pair<int64_t, int64_t>> ways;
    dists[0] = 0;
    ways.insert(make_pair(dists[0], 0));
    for (int64_t i = 0; i < edges; ++i) {
        int64_t first, second, cost;
        cin >> first >> second >> cost;
        graph[first][second] = cost;
    }
    while (!ways.empty()) {
        int64_t node = ways.begin()->second;
        ways.erase(ways.begin());
        for (auto const &item : graph[node]) {
            int64_t destination = item.first;
            int64_t length = item.second;
            if (dists[node] + length < dists[destination]) {
                ways.erase(make_pair(dists[destination], destination));
                dists[destination] = dists[node] + length;
                ways.insert(make_pair(dists[destination], destination));
            }
        }
    }
    for (int64_t i = 1; i < vertices; ++i) {
        cout << dists[i] << "\n";
    }
    return 0;
}
