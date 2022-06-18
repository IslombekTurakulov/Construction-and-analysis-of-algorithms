#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <unordered_map>

using std::cin;
using std::cout;
using std::max_element;
using std::swap;
using std::vector;

struct Drones {
    int id;
    int weight;

    Drones(int id, int weight) {
        this->id = id;
        this->weight = weight;
    }
};

int methodSearch(const vector<Drones> &vector, int left, int right, Drones temp);

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int length;
    cin >> length;
    vector<Drones> vector;
    for (int index_vector = 0; index_vector < length; ++index_vector) {
        int id, weight;
        cin >> id >> weight;
        Drones drone = Drones(id, weight);
        vector.push_back(drone);
        int first_index = vector.size() - 1;
        if (vector.size() > 1 && vector[first_index - 1].weight >= vector[first_index].weight) {
            int left = 0;
            int right = first_index - 1;
            Drones temp_drone = vector[first_index];
            left = methodSearch(vector, left, right, temp_drone);
            for (int index = first_index - 1; index >= left; --index) {
                vector[index + 1] = vector[index];
            }
            vector[left] = temp_drone;
        }
    }
    for (int i = length - 1; i >= 0; --i) {
        cout << vector[i].id << " " << vector[i].weight << "\n";
    }
    return 0;
}

int methodSearch(const vector<Drones> &vector, int left, int right, Drones temp) {
    do {
        int middle = (left + right) / 2;
        vector[middle].weight < temp.weight ? (left = middle + 1) : (right = middle - 1);
    } while (left <= right);
    return left;
}
