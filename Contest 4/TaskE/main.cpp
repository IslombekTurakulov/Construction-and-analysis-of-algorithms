#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

int main() {
    int buttons, pressed_buttons;
    cin >> buttons;
    vector<int> first_vector(buttons);
    for (int i = 0; i < buttons; ++i) {
        cin >> first_vector[i];
    }
    cin >> pressed_buttons;
    vector<int> second_vector(pressed_buttons);
    vector<int> result(pressed_buttons);
    for (int i = 0; i < pressed_buttons; ++i) {
        cin >> second_vector[i];
        ++result[second_vector[i] - 1];
    }
    for (int i = 0; i < first_vector.size(); ++i) {
        cout << (result[i] > first_vector[i] ? "yes" : "no") << "\n";
    }
    return 0;
}
