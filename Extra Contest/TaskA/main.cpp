/**
 * Первая версия [на 22 балла]
 * Версия включала в себя (де-)кодирование через height
 * Использовали разделение битов и начальный размер (10).
 * Вторая версия [на 116 баллов] и [на 172 баллов]
 * Версия теперь с (де-)кодирование  через height и width.
 * Методы getEncodedString и getDecodedString остаётся теми же.
 * В чём вообще алгоритм и смысл решения?
 * Пусть у нас дана матрица 4x4, которая выглядит следующим образом:
 * 0011
 * 0001
 * 1100
 * 0000
 * Проходимся вложенным циклом по матрице и как только находим чёрную клетку (1) пробуем создать
 * прямоугольник наибольшей величины. Всё это делается жадным алгоритмом. Сначала пытаемся получить
 * наибольшую длину, т.е. идём вправо когда есть чёрная клетка Например, в верхней строчке мы
 * начинаем с индекса 2 и заканчиваем индексом 3 поняв, что матрица закончилась. Пытаемся получить
 * как можно большую высоту. Идём вниз и проверяем есть под нашей черной полоской такая же черная
 * полоска, если нет, прерываем. Прямоугольник построен. Получили список прямоугольников, в данном
 * примере три. Кодируем их левый нижний угол и правый верхний. При раскодировке сначала получаем
 * размеры матрицы, изначально она будет иметь только белые клетки (0), потом проходимся по всем
 * прямоугольникам и закрашиваем от левого нижнего и правого верхнего черным цветом (1).
 */

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>

using std::cin;
using std::cout;
using std::log2;
using std::max;
using std::string;
using std::vector;

struct Figure {
    int first_start;
    int second_start;
    int first_end;
    int second_end;
};

void checkTilesOfMatrix(int width, int height, vector<vector<bool>> *result,
                        vector<string> *code_arr);

int checkHeightValue(int height, const vector<string> &code_arr, int second, int points,
                     int temp_index, bool flag);

void checkLengthOfBlock(const string &enc_result, int length_of_block, vector<Figure> *arr);

void showDecodeResult(int width, int height, const vector<vector<bool>> &result);

string getEncodedString(int number, int len) {
    string result;
    while (number > 0) {
        result += static_cast<char>(number % 2 + '0');
        number /= 2;
    }
    while (result.length() < len) {
        result += '0';
    }
    std::reverse(result.begin(), result.end());
    return result;
}

int getDecodeString(const string &input) {
    int index = 0;
    int power = 1;
    for (int i = static_cast<int>(input.length() - 1); i >= 0; --i) {
        index += power * (input[i] - '0');
        power *= 2;
    }
    return index;
}

void decode() {
    string enc_result;
    cin >> enc_result;
    int width, height;
    int length_of_block = getDecodeString(enc_result.substr(0, 4));
    height = getDecodeString(enc_result.substr(4, length_of_block));
    width = getDecodeString(enc_result.substr(length_of_block + 4, length_of_block));
    vector<Figure> arr;
    checkLengthOfBlock(enc_result, length_of_block, &arr);
    vector<vector<bool>> result(height, vector<bool>(width, false));
    for (int i = 0; i < arr.size(); ++i) {
        for (int j = arr.at(i).first_start; j < arr.at(i).first_end; ++j) {
            for (int k = arr.at(i).second_start; k < arr.at(i).second_end; ++k) {
                result[j][k] = 1;
            }
        }
    }
    showDecodeResult(width, height, result);
}

void showDecodeResult(int width, int height, const vector<vector<bool>> &result) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            cout << result[i][j];
        }
        cout << "\n";
    }
}

void checkLengthOfBlock(const string &enc_result, int length_of_block, vector<Figure> *arr) {
    for (int i = 2 * length_of_block + 4; i < enc_result.length(); i += (4 * length_of_block)) {
        (*arr).push_back(Figure{
            getDecodeString(enc_result.substr(i, length_of_block)),
            getDecodeString(enc_result.substr(i + length_of_block, length_of_block)),
            getDecodeString(enc_result.substr(i + length_of_block * 2, length_of_block)),
            getDecodeString(enc_result.substr(i + length_of_block * 3, length_of_block)),
        });
    }
}

void encode() {
    int width, height, some_shit;
    cin >> height >> width >> some_shit;
    int length = ceil(log2(max(height, width)));
    // cout << length << "\n";
    string enc_result = getEncodedString(length, 4) + getEncodedString(height, length) +
                        getEncodedString(width, length);
    vector<vector<bool>> result(height, vector<bool>(width, false));
    vector<string> code_arr;
    checkTilesOfMatrix(width, height, &result, &code_arr);
    for (int first = 0; first < height; ++first) {
        for (int second = 0; second < width; ++second) {
            if (!result[first][second]) {
                continue;
            }
            // cout << "a" << "\n";
            int points = second;
            for (int k = second; (k < width) && (code_arr[first][points] == '1'); ++k, ++points) {
            }
            int temp_index = first;
            bool flag = true;
            temp_index = checkHeightValue(height, code_arr, second, points, temp_index, flag);
            for (int k = first; k < temp_index; ++k) {
                for (int l = second; l < points; ++l) {
                    result[k][l] = 0;
                }
            }
            // --temp_index;
            // cout << first << " " << second << "\n" << temp_index << " " << points << "\n";
            enc_result += getEncodedString(first, length) + getEncodedString(second, length) +
                          getEncodedString(temp_index, length) + getEncodedString(points, length);
        }
    }
    cout << "decode" << '\n';
    cout << enc_result << '\n';
    /*  for (int i = 0; i < height; ++i) {
          for (int j = 0; j < width; ++j) {
              cout << result[i][j];
          }
          cout << "\n";
      }*/
}
int checkHeightValue(int height, const vector<string> &code_arr, int second, int points,
                     int temp_index, bool flag) {
    while (temp_index < height) {
        for (int k = second; k < points; ++k) {
            if (code_arr[temp_index][k] != '1') {
                flag = false;
                break;
            }
        }
        if (!flag) {
            break;
        }
        ++temp_index;
    }
    return temp_index;
}

void checkTilesOfMatrix(int width, int height, vector<vector<bool>> *result,
                        vector<string> *code_arr) {
    for (int i = 0; i < height; ++i) {
        string arr;
        cin >> arr;
        (*code_arr).push_back(arr);
        for (int j = 0; j < width; ++j) {
            if (arr[j] == '1') {
                (*result)[i][j] = 1;
            }
        }
    }
}

int main() {
    string input;
    cin >> input;
    if (input == "encode") {
        encode();
    } else {
        decode();
    }
    return 0;
}
