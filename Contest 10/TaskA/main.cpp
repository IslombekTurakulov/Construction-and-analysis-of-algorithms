#include <iostream>
#include <vector>
#include <string>
#include <fstream>

struct Node {
    int offset;
    int length;
    char next;

    Node(int of, int le, char ne) {
        offset = of;
        length = le;
        next = ne;
    }
};

std::string Decode(const std::vector<Node*>& encoded) {
    std::string answer;
    for (auto& node : encoded) {
        if (node->length > 0) {
            int start = answer.length() - node->offset;
            for (int k = 0; k < node->length; k++) {
                answer += answer[start + k];
            }
        }
        answer += node->next;
    }
    return answer;
}

int main() {
    int n;
    std::cin >> n;

    std::vector<Node*> encoded;

    int offset, length;
    char next;
    for (int i = 0; i < n; i++) {
        std::cin >> offset >> length >> next;
        encoded.push_back(new Node(offset, length, next));
    }
    // (0,0,b) (0,0,a) (0,0,r) (0,0,i) (4,8,#)
    std::string decoded = Decode(encoded);
    std::cout << decoded;
    return 0;
}