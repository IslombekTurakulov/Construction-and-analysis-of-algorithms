#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;

void findAvailableMarquee(vector<int64_t>* student_marquees, vector<int64_t>* each_info_marquees);

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int64_t length;
    cin >> length;
    vector<int64_t> each_info_marquees(4);
    vector<int64_t> student_marquees(length, 1);
    while (length != student_marquees.front() && student_marquees.front() < 13) {
        each_info_marquees.assign(4, student_marquees.front());
        each_info_marquees.front() = 0;
        // if (each_info_marquees.size() < 5 && !each_info_marquees.empty()) {
        for (int64_t i = 0; i < student_marquees.size() - 1; ++i) {
            cout << student_marquees.at(i) << " ";
        }
        cout << student_marquees.back() << "\n";
        findAvailableMarquee(&student_marquees, &each_info_marquees);
        ++student_marquees[each_info_marquees.at(0)];
        student_marquees.erase(each_info_marquees.at(0) + 1 + student_marquees.begin(),
                               student_marquees.end());
        student_marquees.resize((student_marquees.size() + length) - each_info_marquees.at(1) - 1,
                                1);
        // }
    }
    if (length <= 12) {
        cout << length;
    }
    return 0;
}

void findAvailableMarquee(vector<int64_t>* student_marquees, vector<int64_t>* each_info_marquees) {
    for (int64_t i = 1; i < student_marquees->size() - 1; ++i) {
        each_info_marquees->at(2) += student_marquees->at(i);
        if (each_info_marquees->at(3) > student_marquees->at(i)) {
            each_info_marquees->at(3) = student_marquees->at(i);
            each_info_marquees->at(0) = i;
            each_info_marquees->at(1) = each_info_marquees->at(2);
        }
    }
}
