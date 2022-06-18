#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::getline;
using std::max;
using std::min;
using std::string;
using std::vector;

struct Vertex {
    int next;
    int go[26];
    int length;
    int link;
    bool is_leaf;

    Vertex() {
        is_leaf = false;
        link = -1;
        length = 0;
        next = -1;
        for (int i = 0; i < 26; ++i) {
            go[i] = -1;
        }
    }
};

class CalcTheAcids {
private:
    vector<Vertex *> root_;
    vector<vector<int>> children_;
    vector<int> parents_;
    vector<int> begin_;
    vector<int> end_;
    vector<int> level_of_depth_;
    int min_of_acids_;

    void depthFirstSearch(int vertex) {
        begin_.at(vertex) = ++min_of_acids_;
        for (int index = 0; index < children_.at(vertex).size(); ++index) {
            const auto &temp = children_.at(vertex).at(index);
            level_of_depth_.at(temp) = level_of_depth_.at(vertex) + 1;
            depthFirstSearch(temp);
        }
        end_.at(vertex) = ++min_of_acids_;
    }

    void initializeData(const string &str) {
        auto length = str.length() + 1;
        parents_.assign(length, -1);
        begin_.assign(length, 0);
        end_.assign(length, 0);
        level_of_depth_.assign(length, 0);
        children_.assign(length, vector<int>());
    }

    void setChild(int child, int parent) {
        parents_.at(child) = parent;
        children_.at(parent).push_back(child);
    }

public:
    CalcTheAcids();

    ~CalcTheAcids();

    int depthLevel(int left, int right);

    void checkNextNode(int number, char character);

    void initializeToRoot(const string &str);

    void suffixInitializer();

    void initializeBySearchRoot(const string &input);
};

CalcTheAcids::CalcTheAcids() {
    root_.push_back(new Vertex());
    min_of_acids_ = 0;
}

CalcTheAcids::~CalcTheAcids() {
    for (int index = 0; index < root_.size(); ++index) {
        delete root_.at(index);
        root_.at(index) = nullptr;
    }
}

int CalcTheAcids::depthLevel(int left, int right) {
    if (begin_.at(right) <= begin_.at(left)) {
        if (end_.at(left) <= end_.at(right)) {
            return level_of_depth_.at(left) - level_of_depth_.at(right);
        } else {
            return -1;
        }
    } else {
        return -1;
    }
}

void CalcTheAcids::initializeToRoot(const string &str) {
    int number = 0;
    for (int i = 0; i < str.length(); ++i) {
        char character = str[i] - 'a';
        checkNextNode(number, character);
        number = root_.at(number)->go[character];
    }
    root_.at(number)->is_leaf = true;
}

void CalcTheAcids::checkNextNode(int number, char character) {
    if (root_.at(number)->go[character] == -1) {
        root_.push_back(new Vertex());
        root_.at(number)->go[character] = root_.size() - 1;
        root_.at(root_.size() - 1)->length = root_.at(number)->length + 1;
    }
}

void CalcTheAcids::suffixInitializer() {
    int left = 0, right = 0;
    vector<int> query(root_.size(), 0);
    for (int i = 0; i < 26; ++i) {
        if (root_.at(0)->go[i] != -1) {
            Vertex *&node = root_.at(0);
            root_.at(node->go[i])->link = 0;
            query[right] = node->go[i];
            ++right;
        } else {
            root_.at(0)->go[i] = 0;
        }
    }
    while (left < right) {
        int vertex = query.at(left);
        int suff_link = root_.at(vertex)->link;
        root_.at(vertex)->next = root_.at(suff_link)->next;
        if (root_.at(suff_link)->is_leaf) {
            root_.at(vertex)->next = suff_link;
        }
        for (int i = 0; i < 26; ++i) {
            if (root_.at(vertex)->go[i] == -1) {
                root_.at(vertex)->go[i] = root_.at(suff_link)->go[i];
            } else {
                root_.at(root_.at(vertex)->go[i])->link = root_.at(suff_link)->go[i];
                query[right] = root_.at(vertex)->go[i];
                ++right;
            }
        }
        ++left;
    }
}

void CalcTheAcids::initializeBySearchRoot(const string &input) {
    initializeData(input);
    int temp = 0;
    for (int i = 0; i < input.length(); ++i) {
        char symbol = input[i] - 'a';
        int next_link = temp = root_.at(temp)->go[symbol];
        if (!root_.at(next_link)->is_leaf) {
            next_link = root_.at(next_link)->next;
        }
        while (next_link != -1) {
            setChild(i - root_.at(next_link)->length + 1, i + 1);
            next_link = root_.at(next_link)->next;
        }
    }
    for (int i = input.length(); i >= 0; --i) {
        if (parents_.at(i) == -1) {
            depthFirstSearch(i);
        }
    }
}

void requestsAcid(CalcTheAcids *acids, int length, const string &main_str);

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int number_of_acids;
    cin >> number_of_acids;
    CalcTheAcids *acids = new CalcTheAcids();
    for (int i = 0; i < number_of_acids; ++i) {
        string input;
        cin >> input;
        acids->initializeToRoot(input);
    }
    string etalon_text;
    cin >> etalon_text;
    acids->suffixInitializer();
    acids->initializeBySearchRoot(etalon_text);
    int length = 0;
    cin >> length;
    for (int i = 0; i < length; ++i) {
        int left, right;
        cin >> left >> right;
        cout << acids->depthLevel(left - 1, right) << "\n";
    }
    cin >> length;
    requestsAcid(acids, length, etalon_text);
    delete acids;
    return 0;
}

void requestsAcid(CalcTheAcids *acids, int length, const string &main_str) {
    for (int first = 0; first < length; ++first) {
        int q, a, b, c, d, e;
        int left_first, right_first;
        int res = 0;
        cin >> q >> a >> b >> c >> d >> e;
        cin >> left_first >> right_first;
        for (int second = 0; second < q; ++second) {
            auto size = main_str.length();
            int left_second = min(left_first % size, right_first % size);
            int right_second = max(left_first % size, right_first % size) + 1;
            int ans = acids->depthLevel(left_second, right_second);
            left_first = (a * left_first + b) % e;
            right_first = (c * right_first + d + ans) % e;
            res += ans != -1 ? ans : 0;
        }
        cout << res % e << "\n";
    }
}
