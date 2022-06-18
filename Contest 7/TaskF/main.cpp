#include <algorithm>
#include <iostream>
#include <string>
#include <utility>

using std::abs;
using std::cin;
using std::cout;
using std::max;
using std::min;
using std::string;
using std::swap;

int wagnerFischer(const string &first, const string &second, int mistakes, int *last, int *cur) {
    int s_size = first.size() + 1;
    int t_size = second.size() + 1;
    int result = 0;
    for (int first_index = 1; first_index < s_size; ++first_index) {
        bool check_row = false;
        cur[0] = first_index;
        int j = max(1, first_index - mistakes);
        for (; j < min(t_size, first_index + mistakes + 1); ++j) {
            int index = first[first_index - 1] == second[j - 1] ? 0 : 1;
            cur[j] = min(min((last[j] + 1), (cur[j - 1] + 1)), (last[j - 1] + index));
            if (cur[j] <= mistakes) {
                check_row = true;
            }
        }
        if (!check_row) {
            result = s_size - 1;
            break;
        }
        j = 0;
        for (; j < t_size; ++j) {
            swap(cur[j], last[j]);
            cur[j] = t_size - 1;
        }
    }
    if (result != s_size - 1) {
        result = last[t_size - 1];
    }
    return result;
}

int commandsInitializer(int commands_amount, int mistakes, const string &input, string *arr) {
    int result = 0;
    for (int iteration = 0; iteration < commands_amount; ++iteration) {
        int t_size = arr[iteration].size() + 1;
        int s_size = input.size() + 1;
        if (abs(s_size - t_size) > mistakes) {
            if (t_size - 1 <= mistakes) {
                ++result;
            }
        } else {
            int *last = new int[t_size];
            int *cur = new int[t_size];
            for (int j = 0; j < t_size; ++j) {
                last[j] = j;
                cur[j] = t_size - 1;
            }
            if (wagnerFischer(input, arr[iteration], mistakes, last, cur) <= mistakes) {
                ++result;
            }
            delete[] last;
            delete[] cur;
        }
    }
    return result;
}

int main() {
    int commands_amount;
    int mistakes;
    int user_commands;
    string input;
    cin >> commands_amount;
    auto *arr_commands = new string[commands_amount];
    for (int i = 0; i < commands_amount; ++i) {
        cin >> input;
        arr_commands[i] = input;
    }
    cin >> mistakes;
    cin >> user_commands;
    for (int user_iterations = 0; user_iterations < user_commands; ++user_iterations) {
        cin >> input;
        cout << commandsInitializer(commands_amount, mistakes, input, arr_commands) << "\n";
    }
    delete[] arr_commands;
    return 0;
}
