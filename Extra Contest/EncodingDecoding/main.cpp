#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::string;
using std::vector;

int block_length;
constexpr int kLilBlock = 4;

struct Rectangle {
    int x_start;
    int y_start;
    int x_end;
    int y_end;
};

string toBinary(int decimal_num, int block) {
    string binary_num;
    while (decimal_num > 0) {
        binary_num.insert(binary_num.cbegin(), static_cast<char>('0' + decimal_num % 2));
        decimal_num /= 2;
    }
    while (binary_num.length() < block) {
        binary_num.insert(binary_num.cbegin(), '0');
    }
    return binary_num;
}

int toDecimal(string const &binary_num) {
    int decimal_num = 0;
    int power = 1;
    for (int i = static_cast<int>(binary_num.length()) - 1; i > -1; --i) {
        decimal_num += static_cast<int>(binary_num[i] == '1') * power;
        power *= 2;
    }
    return decimal_num;
}

int getLog(int num) {
    int ans = 0;
    int two_power = 1;
    while (two_power < num) {
        ++ans;
        two_power *= 2;
    }
    return ans;
}

void encode() {
    int height;
    cin >> height;
    int width;
    cin >> width;
    block_length = getLog(std::max(height, width));
    int rect;
    cin >> rect;
    string encoded =
            toBinary(block_length, 4) +
            toBinary(width, block_length) +
            toBinary(height, block_length);
    vector<string> matrix(height);
    for (int i = 0; i < height; ++i) {
        cin >> matrix[i];
    }
    vector<vector<bool>> took(height, vector<bool>(width));
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            took[i][j] = (matrix[i][j] == '0');
        }
    }

    for (int first_index = 0; first_index < height; ++first_index) {
        for (int second_index = 0; second_index < width; ++second_index) {
            if (took[first_index][second_index]) {
                continue;
            }
            int jndex = second_index;
            while ((jndex < width) && (matrix[first_index][jndex] == '1')) {
                ++jndex;
            }
            int index = first_index;
            bool is_good = true;
            while (index < height) {
                for (int k = second_index; k < jndex; ++k) {
                    if (matrix[index][k] == '0') {
                        is_good = false;
                        break;
                    }
                }
                if (is_good) {
                    ++index;
                } else {
                    break;
                }
            }
            for (int k = first_index; k < index; ++k) {
                for (int l = second_index; l < jndex; ++l) {
                    took[k][l] = true;
                }
            }
            encoded += toBinary(first_index, block_length);
            encoded += toBinary(second_index, block_length);
            encoded += toBinary(index, block_length);
            encoded += toBinary(jndex, block_length);
        }
    }
    cout << "decode" << '\n'
         << encoded << '\n';
}

void decode() {
    string encoded;
    string decoded;
    cin >> encoded;
    block_length = toDecimal(encoded.substr(0, kLilBlock));
    int width = toDecimal(encoded.substr(kLilBlock, block_length));
    int height = toDecimal(encoded.substr(kLilBlock + block_length, block_length));
    vector<vector<bool>> ans(height, vector<bool>(width, false));

    vector<Rectangle> rects(encoded.length() / (4 * block_length));
    int x_start;
    int y_start;
    int x_end;
    int y_end;
    for (int i = 0; i < static_cast<int>(rects.size()); ++i) {
        x_start = toDecimal(encoded.substr(kLilBlock + (i * 4 + 2) * block_length, block_length));
        y_start = toDecimal(encoded.substr(kLilBlock + (i * 4 + 3) * block_length, block_length));
        x_end = toDecimal(encoded.substr(kLilBlock + (i * 4 + 4) * block_length, block_length));
        y_end = toDecimal(encoded.substr(kLilBlock + (i * 4 + 5) * block_length, block_length));
        rects[i] = Rectangle{x_start, y_start, x_end, y_end};
    }
    for (Rectangle rect: rects) {
        for (int i = rect.x_start; i < rect.x_end; ++i) {
            for (int j = rect.y_start; j < rect.y_end; ++j) {
                ans[i][j] = true;
            }
        }
    }
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            cout << ans[i][j];
        }
        cout << '\n';
    }
}

int main() {
    // Speeding up the input / output.
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string command;
    cin >> command;
    if (command == "encode") {
        encode();
    } else {
        decode();
    }

    return 0;
}
