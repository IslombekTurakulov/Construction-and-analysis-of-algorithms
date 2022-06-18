#include <iostream>
#include <vector>
#include <set>
#include <deque>
#include <algorithm>

using std::cin;
using std::cout;
using std::deque;
using std::min;
using std::min_element;
using std::set;
using std::vector;

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int length, interval;
    cin >> length >> interval;
    vector<int> sequences(length);
    deque<int> deque;
    int index = 0;
    for (; index < length; ++index) {
        cin >> sequences[index];
    }
    index = 0;
    while (index < interval) {
        while (!deque.empty()) {
            if (deque.back() > sequences[index]) {
                deque.pop_back();
            } else {
                break;
            }
        }
        deque.push_back(sequences[index]);
        ++index;
    }
    cout << deque.front() << "\n";
    while (index < length) {
        if (deque.front() == sequences[index - interval]) {
            deque.pop_front();
        }
        while (!deque.empty()) {
            if (deque.back() > sequences[index]) {
                deque.pop_back();
            } else {
                break;
            }
        }
        deque.push_back(sequences[index]);
        cout << deque.front() << "\n";
        ++index;
    }
    return 0;
}
