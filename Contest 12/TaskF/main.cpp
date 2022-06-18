#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>

using std::cin;
using std::cout;
using std::pair;
using std::vector;

void recurDynamic(int i, int j, int **temp_arr, pair<int, int> *items,
                  vector<pair<int, int>> *res) {
    if (temp_arr[i][j] == 0) {
        return;
    } else if (temp_arr[i - 1][j] == temp_arr[i][j]) {
        recurDynamic(i - 1, j, temp_arr, items, res);
    } else {
        recurDynamic(i - 1, j - items[i - 1].first, temp_arr, items, res);
        (*res).push_back(items[i - 1]);
    }
}

vector<pair<int, int>> solve(int products, int weights, pair<int, int> *items) {
    vector<pair<int, int>> res;
    int **temp_arr = new int *[products + 1];
    for (int i = 0; i <= products; ++i) {
        temp_arr[i] = new int[weights + 1];
    }
    for (int i = 0; i <= weights; ++i) {
        temp_arr[0][i] = 0;
    }
    for (int i = 1; i <= products; ++i) {
        for (int j = 0; j <= weights; ++j) {
            temp_arr[i][j] = temp_arr[i - 1][j];
            if (j - items[i - 1].first >= 0) {
                temp_arr[i][j] = std::max(
                    temp_arr[i][j], temp_arr[i - 1][j - items[i - 1].first] + items[i - 1].second);
            }
        }
    }
    recurDynamic(products, weights, temp_arr, items, &res);
    for (int i = 0; i <= products; ++i) {
        delete[] temp_arr[i];
    }
    delete[] temp_arr;
    return res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int products, weights;
    cin >> products >> weights;
    pair<int, int> *arr = new pair<int, int>[products];
    for (int i = 0; i < products; ++i) {
        cin >> arr[i].first;
    }
    for (int i = 0; i < products; ++i) {
        cin >> arr[i].second;
    }
    auto res = solve(products, weights, arr);
    int cost = 0;
    int weight = 0;
    for (int i = 0; i < res.size(); ++i) {
        weight += res[i].first;
        cost += res[i].second;
    }
    cout << cost << "\n" << weight << "\n" << res.size() << "\n";
    for (int i = res.size() - 1; i >= 0; --i) {
        cout << res[i].first << " ";
    }
    cout << "\n";
    for (int i = res.size() - 1; i >= 0; --i) {
        cout << res[i].second << " ";
    }
    delete[] arr;
    return 0;
}
