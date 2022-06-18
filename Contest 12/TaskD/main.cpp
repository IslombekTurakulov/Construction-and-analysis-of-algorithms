/*
 * Красно-черное дерево уровня i состоит из вершины
 * уровня i которая соединена с корнями двух деревьев уровня i − 2 и уровня i−1
 */
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::string;
using std::vector;

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    const int max_length = 2000005;
    const int modularity = 1000000007;
    int64_t length;
    cin >> length;
    int64_t *array_tree = new int64_t[max_length];
    array_tree[0] = 0;
    array_tree[1] = 0;
    array_tree[2] = 4;
    for (int i = 3; i < max_length; ++i) {
        array_tree[i] =
            (array_tree[i - 1] + (2 * array_tree[i - 2] + (i % 3 == 2) * 4)) % modularity;
    }
    while (length) {
        int nums;
        cin >> nums;
        // За один шаг Дио может выбрать 4 вершины
        cout << array_tree[nums - 1] % modularity << "\n";
        --length;
    }
    delete[] array_tree;
    return 0;
}
