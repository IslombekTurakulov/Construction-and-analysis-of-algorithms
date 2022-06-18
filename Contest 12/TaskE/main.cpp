#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using std::cin;
using std::cout;
using std::pair;
using std::sort;
using std::string;
using std::swap;
using std::vector;

void sortWeightsAndCosts(int available_products, vector<pair<int, int>> *weights_and_costs);

bool comp(const pair<int, int> &left, const pair<int, int> &right) {
    if (left.first != right.first) {
        return left.first > right.first;
    }
    return left.second > right.second;
}

int main() {
    int available_products;
    int max_weight_of_backpack;
    cin >> available_products >> max_weight_of_backpack;
    vector<pair<int, int>> weights_and_costs(available_products);
    for (int i = 0; i < available_products; ++i) {
        cin >> weights_and_costs[i].first;
    }
    for (int i = 0; i < available_products; ++i) {
        cin >> weights_and_costs[i].second;
    }
    sortWeightsAndCosts(available_products, &weights_and_costs);
    vector<pair<int, int>> res;
    int weight = 0;
    for (int i = 0; i < available_products; ++i) {
        if ((weight + weights_and_costs[i].first) <= max_weight_of_backpack) {
            res.push_back(weights_and_costs[i]);
            weight += weights_and_costs[i].first;
        }
    }
    int sum_cost = 0, sum_weight = 0;
    for (int i = 0; i < res.size(); ++i) {
        sum_weight += res[i].first;
        sum_cost += res[i].second;
    }
    sort(res.begin(), res.end(), comp);
    cout << sum_cost << "\n" << sum_weight << "\n" << res.size() << "\n";
    for (int i = 0; i < res.size(); ++i) {
        cout << res[i].first << " ";
    }
    cout << "\n";
    for (int i = 0; i < res.size(); ++i) {
        cout << res[i].second << " ";
    }
    return 0;
}

void sortWeightsAndCosts(int available_products, vector<pair<int, int>> *weights_and_costs) {
    for (int first_index = 0; first_index < available_products - 1; ++first_index) {
        for (int second_index = 0; second_index < available_products - first_index - 1;
             ++second_index) {
            double first_weight = static_cast<double>((*weights_and_costs)[second_index].first);
            double second_weight =
                static_cast<double>((*weights_and_costs)[second_index + 1].first);
            double first_divided = (*weights_and_costs)[second_index].second / first_weight;
            double second_divided = (*weights_and_costs)[second_index + 1].second / second_weight;
            bool check_weights = (*weights_and_costs)[second_index].first <
                                 (*weights_and_costs)[second_index + 1].first;
            if (first_divided < second_divided) {
                swap((*weights_and_costs)[second_index], (*weights_and_costs)[second_index + 1]);
            }
            if (first_divided == second_divided && check_weights) {
                swap((*weights_and_costs)[second_index], (*weights_and_costs)[second_index + 1]);
            }
        }
    }
}
