#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <map>

using std::cin;
using std::cout;
using std::map;
using std::string;
using std::vector;

struct Node {
    string university;
    int64_t id;
};

int main() {
    map<string, int64_t> university_teams;
    int64_t length;
    int64_t required_teams;
    int64_t teams_from_university;
    int64_t invited_teams = 0;
    int64_t index = 0;
    cin >> length >> required_teams >> teams_from_university;
    vector<Node> all_teams(length);
    // Я без понятия как это сработало, но это сработало...
    cin.get();
    while (index < length) {
        getline(cin, all_teams[index].university);
        ++index;
    }
    index = 0;
    while (index < length) {
        cin >> all_teams[index].id;
        ++index;
    }
    for (auto const &team: all_teams) {
        if (invited_teams < required_teams) {
            auto iterator = university_teams.insert(make_pair(team.university, 0)).first;
            if (++iterator->second <= teams_from_university) {
                cout << team.university << " #" << team.id << "\n";
                ++invited_teams;
            }
        } else {
            break;
        }
    }
    return 0;
}
