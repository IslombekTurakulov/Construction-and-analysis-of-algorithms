#include <iostream>
#include <initializer_list>
#include <vector>
#include <algorithm>
#include <utility>

using std::cout;
using std::swap;
using std::vector;

template<class ValueType>
class Heap {
private:
    vector<ValueType> arr_;
    size_t size_{};

    void fixHeap(int index) {
        size_t left = getLeft(index);
        size_t right = getRight(index);
        size_t current = index;
        if (left < size_ && arr_[left] > arr_[current]) {
            current = left;
        }
        if (right < size_ && arr_[right] > arr_[current]) {
            current = right;
        }
        if (current != index) {
            std::swap(arr_[index], arr_[current]);
            fixHeap(current);
        }
    }

    [[nodiscard]] int getRight(int index) const {
        return 2 * index + 2;
    }

    [[nodiscard]] int getLeft(int index) const {
        return 2 * index + 1;
    }

    void bubbleUp() {
        size_t index = size_;
        size_t middle = (size_ - 1) / 2;
        while (0 < index && arr_[middle] < arr_[index]) {
            swap(arr_[middle], arr_[index]);
            index = middle;
            middle = (middle - 1) / 2;
        }
    }

public:
    Heap() {
        arr_ = vector<ValueType>();
        size_ = 0;
    }

    ~Heap() = default;

    Heap(const Heap &other) {
        size_ = other.size_;
        arr_ = other.arr_;
    }

    Heap &operator=(const Heap &other) {
        if (&other == this) {
            return *this;
        }
        size_ = other.size_;
        arr_ = other.arr_;
        return *this;
    }

    Heap(Heap &&other) noexcept {
        size_ = other.size_;
        arr_ = other.arr_;
        other.size_ = 0;
        other.arr_.clear();
    }

    Heap &operator=(Heap &&other) noexcept {
        if (&other == this) {
            return *this;
        }
        size_ = other.size_;
        arr_ = other.arr_;
        clearHeap(other);
        return *this;
    }

    void clearHeap(Heap &&other) const {
        other.size_ = 0;
        other.arr_.clear();
    }

    template<class Iterator>
    Heap(Iterator begin, Iterator end) {
        while (begin != end) {
            insert(*begin);
            ++begin;
        }
    }

    Heap(std::initializer_list<ValueType> list) {
        for (ValueType item: list) {
            insert(item);
        }
    }

    [[nodiscard]] size_t size() const {
        return size_;
    }

    [[nodiscard]] bool empty() const {
        return size_ <= 0;
    }

    void insert(const ValueType &value) {
        arr_.push_back(value);
        bubbleUp();
        ++size_;
    }

    ValueType extract() {
        ValueType result = getFirstValue();
        --size_;
        fixHeap(0);
        return result;
    }

    ValueType getFirstValue() {
        ValueType result = arr_[0];
        arr_[0] = arr_.back();
        arr_.pop_back();
        return result;
    }
};


int main() {
    Heap<int> heap = *new Heap<int>();
    heap.insert(1);
    heap.insert(2);
    cout << heap.size() << "\n";
    Heap<int> heap_2{1, 2, 4, 5, 2};
    cout << heap_2.size();
    return 0;
}
