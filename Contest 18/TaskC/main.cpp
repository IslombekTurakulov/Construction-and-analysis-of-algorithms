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
    uint32_t tracks, track_interval, hackathon_number;
    cin >> tracks >> track_interval >> hackathon_number;
    vector<uint32_t> arr_interval(track_interval, 1);
    int iteration = 1;
    while (iteration < hackathon_number) {
        for (uint32_t i = arr_interval.size() - 1; i >= 0; --i) {
            ++arr_interval[i];
            if (arr_interval[i] > tracks) {
                arr_interval[i] = 1;
            } else {
                break;
            }
        }
        ++iteration;
    }
    for (uint32_t i = 1; i <= arr_interval.size(); ++i) {
        cout << arr_interval[i - 1] << (i == arr_interval.size() ? "" : " ");
    }
    return 0;
}