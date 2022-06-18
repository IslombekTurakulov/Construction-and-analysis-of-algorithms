// https://cyberleninka.ru/article/n/razbor-zadach-pyatoy-vserossiyskoy-komandnoy-olimpiady-shkolnikov-po-programmirovaniyu-2/viewer
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

using std::cin;
using std::cout;
using std::make_pair;
using std::max;
using std::min;
using std::pair;
using std::set;
using std::string;
using std::swap;
using std::vector;

constexpr double kEpsilon = 1E-7;

struct Vertex {
    double x, y;
    Vertex(double x, double y) : x(x), y(y) {
    }

    Vertex() : x(0), y(0) {
    }

    Vertex rotate(double cos, double sin) {
        return Vertex(x * cos + y * sin, -x * sin + y * cos);
    }

    double vectorLength() const {
        return sqrt((x * x) + (y * y));
    }

    double tan() const {
        return atan2(y, x);
    }
};

Vertex add(const Vertex &first, const Vertex &second) {
    return Vertex(first.x + second.x, first.y + second.y);
}

Vertex diff(const Vertex &first, const Vertex &second) {
    return Vertex(first.x - second.x, first.y - second.y);
}

Vertex mult(const Vertex &vertex, double constant) {
    return Vertex(constant * vertex.x, constant * vertex.y);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    vector<pair<Vertex, double>> circles;
    for (int index = 0; index < 2; ++index) {
        double coord_x, coord_y, radius;
        cin >> coord_x >> coord_y >> radius;
        circles.push_back(make_pair(Vertex(coord_x, coord_y), radius));
    }
    if (circles.at(0).second > circles.at(1).second) {
        swap(circles.at(0), circles.at(1));
    }
    vector<Vertex> vertex_coords;
    for (int index = 0; index < 2; ++index) {
        double x, y;
        cin >> x >> y;
        vertex_coords.push_back(Vertex(x, y));
    }
    Vertex &first_vertex = circles.at(1).first;
    double second_vertex = circles.at(1).second;
    auto length = diff(first_vertex, circles.at(0).first).vectorLength();
    if (length + kEpsilon >= second_vertex + circles.at(0).second ||
        length - kEpsilon <= second_vertex - circles.at(0).second) {
        if (fabs(length - (second_vertex - circles.at(0).second)) < kEpsilon ||
            fabs(length - (second_vertex + circles.at(0).second)) < kEpsilon) {
            vertex_coords.push_back(
                add(mult(diff(circles.at(0).first, first_vertex), (second_vertex / length)),
                    first_vertex));
        }
    } else {
        auto temp_coord = (circles.at(0).second * circles.at(0).second -
                           second_vertex * second_vertex + length * length) /
                          (2 * length);
        auto height = sqrt(circles.at(0).second * circles.at(0).second - temp_coord * temp_coord);
        double cos_num = temp_coord / circles.at(0).second;
        vertex_coords.push_back(add(mult(diff(first_vertex, circles.at(0).first)
                                             .rotate(cos_num, height / circles.at(0).second),
                                         (circles.at(0).second / length)),
                                    circles.at(0).first));
        vertex_coords.push_back(add(mult(diff(first_vertex, circles.at(0).first)
                                             .rotate(cos_num, -height / circles.at(0).second),
                                         (circles.at(0).second / length)),
                                    circles.at(0).first));
    }
    vector<vector<double>> arr_vec(vertex_coords.size(), vector<double>(vertex_coords.size()));
    for (int i = 0; i < arr_vec.size(); ++i) {
        for (int j = 0; j < arr_vec.at(i).size(); ++j) {
            if (i == j) {
                arr_vec.at(i).at(j) = 0;
            } else {
                arr_vec.at(i).at(j) = -1;
            }
        }
    }
    for (int first = 0; first < circles.size(); ++first) {
        for (int second = 0; second < vertex_coords.size(); ++second) {
            if (fabs(diff(vertex_coords.at(second), circles.at(first).first).vectorLength() -
                     circles.at(first).second) < kEpsilon) {
                for (int third = 0; third < vertex_coords.size(); ++third) {
                    if (fabs(diff(vertex_coords.at(third), circles.at(first).first).vectorLength() -
                             circles.at(first).second) >= kEpsilon) {
                        continue;
                    }
                    auto first1 = diff(vertex_coords.at(second), circles.at(first).first).tan();
                    auto second1 = diff(vertex_coords.at(third), circles.at(first).first).tan();
                    if (first1 > second1) {
                        swap(first1, second1);
                    }
                    auto distance = min(second1 - first1, first1 + 2 * M_PI - second1) *
                                    circles.at(first).second;
                    if (arr_vec.at(second).at(third) < -0.5 ||
                        arr_vec.at(second).at(third) > distance) {
                        arr_vec.at(second).at(third) = distance;
                    }
                }
            }
        }
    }
    for (int first = 0; first < vertex_coords.size(); ++first) {
        for (int second = 0; second < vertex_coords.size(); ++second) {
            for (int third = 0; third < vertex_coords.size(); ++third) {
                if ((arr_vec.at(second).at(first) > -0.5) && (arr_vec.at(first).at(third) > -0.5)) {
                    if ((arr_vec.at(second).at(third) < -0.5) ||
                        (arr_vec.at(second).at(third) >
                         arr_vec.at(second).at(first) + arr_vec.at(first).at(third))) {
                        arr_vec.at(second).at(third) =
                            arr_vec.at(second).at(first) + arr_vec.at(first).at(third);
                    }
                }
            }
        }
    }
    cout << std::setprecision(10);
    if (arr_vec.at(0).at(1) >= -0.5) {
        cout << arr_vec.at(0).at(1);
    } else {
        cout << -1;
    }
    return 0;
}
