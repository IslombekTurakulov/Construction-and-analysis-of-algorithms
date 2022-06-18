// Алгоритм (что такое родословное дерево)
// был взят отсюда:
// https://shashkovs.ru/_prog_b22/pgm18__Graphs-1.html#Kornevie_derev_ya
#include <iostream>
#include <string>
#include <map>

using std::cin;
using std::cout;
using std::map;
using std::string;

int main() {
    int length;
    map<string, string> family_tree;
    string name, parent;
    cin >> length;
    for (int index = 0; index < length - 1; ++index) {
        cin >> name >> parent;
        family_tree[name] = parent;
    }
    for (const auto &cell : family_tree) {
        int height = 0;
        name = cell.first;
        while (!family_tree[name].empty()) {
            name = family_tree[name];
            ++height;
        }
        cout << cell.first << ' ' << height << "\n";
    }
    return 0;
}
