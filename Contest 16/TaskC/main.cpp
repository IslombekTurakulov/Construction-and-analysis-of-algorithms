#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

using std::cin;
using std::cout;
using std::make_pair;
using std::map;
using std::min;
using std::string;
using std::vector;

int max = 0;

struct Edges {
    int from, to, flow;
};

int findByKey(char symbol) {
    if (symbol == 'C') {
        return 4;
    } else if (symbol == 'O') {
        return 2;
    } else if (symbol == 'N') {
        return 3;
    } else if (symbol == 'H') {
        return 1;
    } else {
        return 0;
    }
}

int backEdge(Edges edge, const vector<vector<Edges>> &vec_edge);

int parseVer(int i, int j, int width);

int push(vector<vector<Edges>> *vec_edge, vector<bool> *visited, const int &area, int current = 0,
         int capacity = 5) {
    (*visited)[current] = true;
    if (current != area - 1) {
        for (int index = 0; index < (*vec_edge)[current].size(); ++index) {
            if ((*visited)[(*vec_edge)[current][index].to] ||
                (*vec_edge)[current][index].flow == 0) {
                continue;
            }
            Edges node = (*vec_edge)[current][index];
            int min_cap = push(vec_edge, visited, area, node.to, min(node.flow, capacity));
            if (min_cap > 0) {
                (*vec_edge)[current][index].flow -= min_cap;
                int back_edge_num = backEdge(node, *vec_edge);
                if (back_edge_num != -1) {
                    (*vec_edge)[node.to][back_edge_num].flow += min_cap;
                } else {
                    (*vec_edge)[node.to].push_back(
                        Edges{.from = node.to, .to = current, .flow = min_cap});
                }
                return min_cap;
            }
        }
        capacity = 0;
    } else {
        max += capacity;
    }
    return capacity;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int height, width, sum = 0, target_sum = 0;
    cin >> height >> width;
    int area = height * width + 2;
    vector<bool> visited(area, false);
    vector<vector<Edges>> edge(area);
    /* map<char, int> map;
    map.insert(make_pair('H', 1));
    map.insert(make_pair('O', 2));
    map.insert(make_pair('N', 3));
    map.insert(make_pair('c', 4));*/
    for (int first = 0; first < height; ++first) {
        for (int second = 0; second < width; ++second) {
            char symbol;
            cin >> symbol;
            int from = parseVer(first, second, width);
            if (((first % 2) + (second % 2)) % 2 == 0) {
                sum += findByKey(symbol);
                edge[0].push_back(Edges{.from = 0, .to = from, .flow = findByKey(symbol)});
                if (first + 1 < height) {
                    edge[from].push_back(
                        Edges{.from = from, .to = parseVer(first + 1, second, width), .flow = 1});
                }
                if (second + 1 < width) {
                    edge[from].push_back(
                        Edges{.from = from, .to = parseVer(first, second + 1, width), .flow = 1});
                }
                if (first - 1 >= 0) {
                    edge[from].push_back(
                        Edges{.from = from, .to = parseVer(first - 1, second, width), .flow = 1});
                }
                if (second - 1 >= 0) {
                    edge[from].push_back(
                        Edges{.from = from, .to = parseVer(first, second - 1, width), .flow = 1});
                }
            } else {
                target_sum += findByKey(symbol);
                edge[from].push_back(
                    Edges{.from = from, .to = area - 1, .flow = findByKey(symbol)});
            }
        }
    }
    while (push(&edge, &visited, area)) {
        for (int i = 0; i < area; ++i) {
            visited[i] = false;
        }
    }
    if ((max == sum) && (max == target_sum)) {
        cout << (max != 0 ? "Valid" : "Invalid") << "\n";
    } else {
        cout << "Invalid"
             << "\n";
    }
}

int parseVer(int i, int j, int width) {
    return (i * width) + (j + 1);
}

int backEdge(Edges edge, const vector<vector<Edges>> &vec_edge) {
    for (int i = 0; i < vec_edge[edge.to].size(); ++i) {
        if (vec_edge[edge.to][i].to == edge.from) {
            return i;
        }
    }
    return -1;
}
