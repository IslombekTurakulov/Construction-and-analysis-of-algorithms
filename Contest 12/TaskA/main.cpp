#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::max;
using std::sort;
using std::string;
using std::vector;

vector<int64_t> red_array, green_array, blue_array;
int red_length, green_length, blue_length;
int64_t array_of_colors[302][302][302] = {0};

bool comp(int64_t a, int64_t b) {
    return a > b;
}

int64_t findSolution(int red, int green, int blue) {
    if (array_of_colors[red][green][blue] != 0) {
        return array_of_colors[red][green][blue];
    }
    int64_t area = 0;
    if (red <= red_length && green <= green_length) {
        area =
            max(area, findSolution(red + 1, green + 1, blue) + red_array[red] * green_array[green]);
    }
    if (green <= green_length && blue <= blue_length) {
        area = max(area,
                   findSolution(red, green + 1, blue + 1) + green_array[green] * blue_array[blue]);
    }
    if (red <= red_length && blue <= blue_length) {
        area =
            max(area, findSolution(red + 1, green, blue + 1) + red_array[red] * blue_array[blue]);
    }
    return array_of_colors[red][green][blue] = area;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> red_length >> green_length >> blue_length;
    red_array.resize(red_length + 1);
    green_array.resize(green_length + 1);
    blue_array.resize(blue_length + 1);
    for (int i = 1; i <= red_length; ++i) {
        cin >> red_array[i];
    }
    for (int i = 1; i <= green_length; ++i) {
        cin >> green_array[i];
    }
    for (int i = 1; i <= blue_length; ++i) {
        cin >> blue_array[i];
    }
    sort(1 + red_array.begin(), red_array.end(), comp);
    sort(1 + green_array.begin(), green_array.end(), comp);
    sort(1 + blue_array.begin(), blue_array.end(), comp);
    cout << findSolution(1, 1, 1);
    return 0;
}
