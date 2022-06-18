// Использовал сортировку выбором
#include <iostream>
#include <vector>
#include <sstream>
#include <utility>
#include <string>

using std::cin;
using std::cout;
using std::string;
using std::stringstream;
using std::swap;
using std::vector;

vector<int64_t> split(const std::string &s, char delim) {
    vector<int64_t> elems;
    stringstream ss;
    ss.str(s);
    string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(stoi(item));
    }
    return elems;
}

int64_t searchMin(int64_t length, const vector<int64_t> &vec, int64_t index, int64_t minimum) {
    int64_t temp_index = index;
    for (int64_t second_index = index; second_index < length; ++second_index) {
        if (vec[second_index] < minimum) {
            minimum = vec[second_index];
            temp_index = second_index;
        }
    }
    return temp_index;
}

vector<int64_t> algoMethod(const string &input) {
    vector<int64_t> vector = split(input, ' ');
    for (int64_t first_index = 0; first_index < vector.size(); ++first_index) {
        int64_t minimum = vector[first_index];
        int64_t temp_index = searchMin(vector.size(), vector, first_index, minimum);
        if (first_index != temp_index) {
            swap(vector[first_index], vector[temp_index]);
        }
    }
    return vector;
}

int search(int elem) {
    int arr[11] = {1, 2, 2, 4, 4, 5, 5, 6, 6, 6, 7};
    int left = -1;
    int right = 11;
    while (right - left > 1) {
        int mid = (left + right) / 2;
        if (arr[mid] <= elem)
            left = mid;
        else
            right = mid;
    }
    return left;
}

int main() {
    cout << search(11) << "\n";

    /* string first_input;
     string second_input;
     getline(cin, first_input);
     getline(cin, second_input);
     vector<int64_t> money = algoMethod(first_input);
     vector<int64_t> distance = algoMethod(second_input);
     auto first = distance.begin();
     auto last = distance.end() - 1;
     while (first < last) {
         swap(*first, *last);
         ++first;
         --last;
     }
     int64_t sum = 0;
     for (int i = 0; i < money.size(); ++i) {
         sum += money[i] * distance[i];
     }
     cout << sum << "\n";*/
    return 0;
}
