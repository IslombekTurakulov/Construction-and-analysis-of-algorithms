#include <iostream>
#include <vector>
#include <string>
#include <map>

using std::cin;
using std::cout;
using std::map;
using std::string;
using std::vector;

struct Vertex {
    vector<Vertex*> children;
    vector<Vertex*> next;
    Vertex* parent;
    Vertex* suffix;
    bool is_counted;
    bool is_leaf;
    int64_t counter;
    char symbol_num;
    vector<int> leaf_id;

    Vertex(Vertex* current, char to_par) {
        parent = current;
        suffix = nullptr;
        symbol_num = to_par;
        is_leaf = false;
        is_counted = false;
        counter = 0;
        children.assign(2, nullptr);
        next.assign(2, nullptr);
    }
};

Vertex* root;

map<Vertex*, int> color;

Vertex* getSuffix(Vertex* node, char symbol);

Vertex* suffSymbol(Vertex* node) {
    if (node != nullptr) {
        if (node->suffix == nullptr) {
            node->suffix = node == root || node->parent == root
                               ? root
                               : getSuffix(suffSymbol(node->parent), node->symbol_num);
        }
        return node->suffix;
    } else {
        return nullptr;
    }
}

Vertex* getSuffix(Vertex* node, char symbol) {
    char new_symbol = symbol - '0';
    if (node->next[new_symbol] == nullptr) {
        if (node->children[new_symbol] != nullptr) {
            node->next[new_symbol] = node->children[new_symbol];
        } else if (node == root) {
            node->next[new_symbol] = root;
        } else {
            node->next[new_symbol] = getSuffix(suffSymbol(node), symbol);
        }
    }
    return node->next[new_symbol];
}

void initializeToRoot(const std::string& input, int pattern_number) {
    Vertex* cur = root;
    for (auto i = 0; i < input.size(); ++i) {
        char symbol = input[i] - '0';
        if (cur->children[symbol] == nullptr) {
            cur->children[symbol] = new Vertex(cur, input[i]);
        }
        cur = cur->children[symbol];
    }
    cur->leaf_id.push_back(pattern_number);
    cur->is_leaf = true;
}

int64_t getCounter(Vertex* node) {
    if (node != nullptr) {
        if (!node->is_counted) {
            node->is_counted = true;
            if (node == root) {
                node->counter = 0;
            } else {
                if (node->is_leaf) {
                    node->counter += node->leaf_id.size();
                }
                node->counter += getCounter(suffSymbol(node));
            }
        }
        return node->counter;
    } else {
        return 0;
    }
}

bool depthFirstSearch(Vertex* node) {
    color[node] = 1;
    for (int i = 0; i < 2; ++i) {
        Vertex* next = getSuffix(node, static_cast<char>(i + '0'));
        if (color.count(next) == 0 && getCounter(next) == 0
                ? depthFirstSearch(next)
                : getCounter(next) == 0 && color[next] == 1) {
            return true;
        }
    }
    color[node] = 2;
    return false;
}

int main() {
    std::ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    int length;
    cin >> length;
    root = new Vertex(nullptr, '0');
    for (int i = 0; i < length; ++i) {
        string str;
        cin >> str;
        initializeToRoot(str, i);
    }
    cout << (depthFirstSearch(root) ? "TAK" : "NIE") << std::endl;
    return 0;
}
