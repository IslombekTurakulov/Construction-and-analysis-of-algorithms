#include <algorithm>
#include <deque>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::deque;
using std::getline;
using std::max;
using std::min;
using std::pair;
using std::string;
using std::vector;

struct Card {
    int weight;
    int house_id;
};

void bfs(vector<vector<Card>> *cards, vector<int> *steps, vector<bool> *color, int current) {
    steps->at(current) = 0;
    std::deque<int> deque;
    deque.push_back(current);
    while (!deque.empty()) {
        int num = deque.front();
        deque.pop_front();
        if (color->at(num) == 0) {
            for (auto vert : cards->at(num)) {
                auto dist = steps->at(num) + vert.weight;
                if (steps->at(vert.house_id) > dist) {
                    steps->at(vert.house_id) = dist;
                    if (vert.weight == 1) {
                        deque.push_back(vert.house_id);
                    } else {
                        deque.push_front(vert.house_id);
                    }
                }
            }
            color->at(num) = 1;
        }
    }
}

int main() {
    int amount_of_houses, amount_of_cards;
    cin >> amount_of_houses >> amount_of_cards;
    int total_size = amount_of_houses * (amount_of_cards + 1) + 2;
    vector<bool> colors(total_size, 0);
    vector<int> horse_ways(total_size, INT32_MAX);
    vector<vector<Card>> cards(total_size, vector<Card>());
    int map_counter = amount_of_houses;
    for (int first_index = 0; first_index < amount_of_cards; ++first_index) {
        int length;
        cin >> length;
        for (int second_index = 0; second_index < length; ++second_index) {
            int start = 0, finish = 0;
            cin >> start >> finish;
            auto first_temp = (start + map_counter) % amount_of_houses == 0
                                  ? amount_of_houses
                                  : (start + map_counter) % amount_of_houses;
            auto second_temp = (finish + map_counter) % amount_of_houses == 0
                                   ? amount_of_houses
                                   : (finish + map_counter) % amount_of_houses;
            cards.at(start + map_counter)
                .push_back(Card{.weight = 0, .house_id = finish + map_counter});
            cards.at(finish + map_counter)
                .push_back(Card{.weight = 0, .house_id = start + map_counter});
            cards.at(start + map_counter).push_back(Card{.weight = 1, .house_id = first_temp});
            cards.at(finish + map_counter).push_back(Card{.weight = 1, .house_id = second_temp});
            cards.at(first_temp).push_back(Card{.weight = 0, .house_id = start + map_counter});
            cards.at(second_temp).push_back(Card{.weight = 0, .house_id = finish + map_counter});
        }
        map_counter += amount_of_houses;
    }
    bfs(&cards, &horse_ways, &colors, 1);
    cout << (horse_ways[amount_of_houses] != INT32_MAX ? horse_ways[amount_of_houses] : -1);
    return 0;
}
