#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::min;
using std::string;
using std::vector;

int64_t max_flow = 0, start_sum = 0, target_sum = 0;


class Edge {
public:
    int from;
    int to;
    int flow;

    Edge(int from = -1, int to = -1, int flow = 0) : from(from), to(to), flow(flow) {
    }
};

class Graph {

public:
    int v_num;
    int height;
    int width;
    vector<bool> checked;
    vector<vector<Edge>> edge;

    Graph(int height, int width);
    void addEdge(int from, int to, int flow);
    void init(int height, int width);
    void uncheckAll();
    int toVertNum(int i, int j);
};

int findByKey(char atom);
int findBackEdge(Graph *g, Edge edge);

Graph::Graph(int height, int width) {
    this->height = height;
    this->width = width;
    this->v_num = height * width + 2;
    checked.resize(v_num, false);
    edge.resize(v_num);
}

int findBackEdge(Graph *g, Edge edge) {
    for (int child = 0; child < g->edge[edge.to].size(); ++child) {
        if (g->edge[edge.to][child].to == edge.from) {
            return child;
        }
    }
    return -1;
}

int findByKey(char atom) {
    switch (atom) {
        case ('H'):
            return 1;
        case ('O'):
            return 2;
        case ('N'):
            return 3;
        case ('C'):
            return 4;
    }
    return 0;
}

void Graph::addEdge(int from, int to, int flow = 1) {
    edge[from].push_back(
            Edge(from, to, flow));
}

void Graph::uncheckAll() {
    for (int i = 0; i < v_num; ++i) {
        checked[i] = false;
    }
}

int Graph::toVertNum(int i, int j) {
    return i * width + j + 1;
}

void Graph::init(int height, int width) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            char atom;
            cin >> atom;
            if (((i % 2) + (j % 2)) % 2 == 0) {
                addEdge(0, toVertNum(i, j), valence(atom));
                start_sum += valence(atom);
                if (i + 1 < height) {
                    addEdge(toVertNum(i, j), toVertNum(i + 1, j));
                }
                if (j + 1 < width) {
                    addEdge(toVertNum(i, j), toVertNum(i, j + 1));
                }
                if (i - 1 >= 0) {
                    addEdge(toVertNum(i, j), toVertNum(i - 1, j));
                }
                if (j - 1 >= 0) {
                    addEdge(toVertNum(i, j), toVertNum(i, j - 1));
                }
            } else {
                addEdge(toVertNum(i, j), v_num - 1, valence(atom));
                target_sum += valence(atom);
            }
        }
    }
}

int tryPushFlow(Graph *graph, int current = 0, int capacity = 5) {
    graph->checked[current] = true;
    if (current != graph->v_num - 1) {
        for (int e = 0; e < graph->edge[current].size(); ++e) {
            Edge edge = graph->edge[current][e];

            if (!graph->checked[edge.to] && edge.flow != 0) {
                int min_capacity = tryPushFlow(graph, edge.to, min(edge.flow, capacity));
                if (min_capacity > 0) {
                    graph->edge[current][e].flow -= min_capacity;
                    int back_edge_num = findBackEdge(graph, edge);
                    if (back_edge_num == -1) {
                        graph->edge[edge.to].push_back(Edge(edge.to, current, min_capacity));
                    } else {
                        graph->edge[edge.to][back_edge_num].flow += min_capacity;
                    }
                    return min_capacity;
                }
            }
        }
        return 0;
    } else {
        max_flow += capacity;
        return capacity;
    }
}

int main() {
    int height, width;
    cin >> height >> width;
    Graph g = Graph(height, width);
    g.init(height, width);

    while (tryPushFlow(&g)) {
        g.uncheckAll();
    }

    (max_flow == start_sum) && (max_flow == target_sum) && (max_flow != 0) ? cout << "Valid" : cout << "Invalid";
}