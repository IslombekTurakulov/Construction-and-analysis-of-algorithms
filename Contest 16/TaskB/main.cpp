#include <algorithm>
#include <climits>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using std::cin;
using std::cout;
using std::fill;
using std::make_pair;
using std::map;
using std::min;
using std::pair;
using std::queue;
using std::string;
using std::vector;

class Graph {
private:
    struct Edges {
        int64_t direction, cost, flow;
    };

    struct Coords {
        int64_t x, y;
    };

    int64_t dfs(int64_t from, int64_t to, int64_t flow, vector<int64_t> *parent,
                vector<int64_t> *distance) {
        if (flow != 0) {
            if (from != to) {
                while (parent->at(from) < edges_[from].size()) {
                    int position = edges_[from][parent->at(from)];
                    int next = bridges_.at(position).direction;
                    if (distance->at(next) == distance->at(from) + 1) {
                        int64_t total =
                            dfs(next, to,
                                min(flow, bridges_.at(position).cost - bridges_.at(position).flow),
                                parent, distance);
                        if (total) {
                            bridges_.at(position).flow += total;
                            bridges_.at(position ^ 1).flow -= total;
                            return total;
                        }
                    }
                    ++parent->at(from);
                }
            } else {
                return flow;
            }
        }
        return 0;
    }

    bool bfs(int64_t from, int64_t to, vector<int64_t> *distance) {
        queue<int64_t> queue;
        queue.push(from);
        distance->at(from) = 0;
        while (!queue.empty() && distance->at(to) == -1) {
            int64_t vertex = queue.front();
            queue.pop();
            for (int64_t index = 0; index < edges_[vertex].size(); ++index) {
                int64_t position = edges_[vertex][index], next = bridges_[position].direction;
                if (distance->at(next) == -1 && bridges_[position].flow < bridges_[position].cost) {
                    queue.push(next);
                    distance->at(next) = distance->at(vertex) + 1;
                }
            }
        }
        return distance->at(to) != -1;
    }

    void addEdge(int from, int to) {
        edges_.at(from).push_back(static_cast<int>(bridges_.size()));
        edges_.at(to).push_back(static_cast<int>(bridges_.size() + 1));
        bridges_.push_back({to, 1, 0});
        bridges_.push_back({from, 0, 0});
    }

    vector<vector<int64_t>> edges_{};
    int64_t length_{}, sum_{};
    map<pair<int64_t, int64_t>, Coords> bridges_coord_{};
    vector<Edges> bridges_{};

public:
    explicit Graph(int length) {
        this->length_ = length;
        sum_ = 0;
        // edges_.reserve((length * 2) + 10);
        edges_.resize((length * 3) + 10);
    }

    void initialize() {
        int64_t x1, y1, x2, y2;
        for (int index = 0; index < length_; ++index) {
            cin >> x1 >> y1 >> x2 >> y2;
            checkVariable(x1, y1), checkVariable(x2, y2);
            addEdge(bridges_coord_.at({x1, y1}).y, bridges_coord_.at({x2, y2}).x);
            addEdge(bridges_coord_.at({x2, y2}).y, bridges_coord_.at({x1, y1}).x);
        }
        cin >> x1 >> y1 >> x2 >> y2;
        checkVariable(x1, y1), checkVariable(x2, y2);
        cout << findFlow(bridges_coord_.at({x1, y1}).y, bridges_coord_.at({x2, y2}).x);
    }

    void checkVariable(int x, int y) {
        if (bridges_coord_[{x, y}].x == 0 && bridges_coord_[{x, y}].y == 0) {
            bridges_coord_[{x, y}] = {sum_, sum_ + 1};
            addEdge(sum_, sum_ + 1);
            sum_ += 2;
        }
    }

    int findFlow(int from, int to) {
        int total_connections = 0;
        vector<int64_t> parent(edges_.size(), 0);
        vector<int64_t> distance(edges_.size(), -1);
        bool loop = true;
        for (; loop;) {
            fill(distance.begin(), distance.end(), -1);
            if (bfs(from, to, &distance)) {
                fill(parent.begin(), parent.end(), 0);
                while (int64_t res = dfs(from, to, INT32_MAX, &parent, &distance)) {
                    total_connections += res;
                }
            } else {
                loop = false;
            }
        }
        return total_connections;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int length;
    cin >> length;
    Graph *graph = new Graph(length);
    graph->initialize();
    delete graph;
    return 0;
}
