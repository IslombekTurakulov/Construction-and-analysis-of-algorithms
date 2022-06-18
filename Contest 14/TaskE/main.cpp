#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

vector<bool> first_used;
vector<bool> second_used;
vector<int> order;
vector<int> component;
vector<int> array[200010];
vector<int> sorted_array[200010];
int index_connections[200010];

void firstDfs(int connection);

void secondDfs(int connection);

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int vertices, edges;
    cin >> vertices >> edges;
    first_used.assign(vertices, false);
    second_used.assign(vertices, false);
    for (int index = 0; index < edges; ++index) {
        int first, second;
        cin >> first >> second;
        sorted_array[second - 1].push_back(first - 1);
        array[first - 1].push_back(second - 1);
    }
    for (int index = 0; index < vertices; ++index) {
        if (first_used[index] == 0) {
            firstDfs(index);
        }
    }
    int connections = 1;
    for (int index = 0; index < vertices; ++index) {
        if (second_used[order[vertices - 1 - index]] == 0) {
            secondDfs(order[vertices - 1 - index]);
            for (auto iterator = component.begin(); iterator != component.end(); ++iterator) {
                index_connections[*iterator] = connections;
            }
            ++connections;
            component.clear();
        }
    }
    cout << connections - 1 << "\n";
    for (int i = 0; i < vertices - 1; ++i) {
        cout << index_connections[i] << " ";
    }
    cout << index_connections[vertices - 1] << "\n";
    return 0;
}

void firstDfs(int connection) {
    first_used[connection] = 1;
    for (int index = 0; index < array[connection].size(); ++index) {
        if (first_used[array[connection][index]] == 0) {
            firstDfs(array[connection][index]);
        }
    }
    order.push_back(connection);
}

void secondDfs(int connection) {
    second_used[connection] = 1;
    component.push_back(connection);
    for (int index = 0; index < sorted_array[connection].size(); ++index) {
        if (second_used[sorted_array[connection][index]] == 0) {
            secondDfs(sorted_array[connection][index]);
        }
    }
}
