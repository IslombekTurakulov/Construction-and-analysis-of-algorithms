#include <vector>
#include <utility>
#include <algorithm>
#include "./student-ski.h"

using std::pair;
using std::swap;
using std::vector;

void partitionStudent(vector<Student> *students, Ski *ski, int *left, int *right) {
    while ((*left) <= (*right)) {
        while (compare((*students)[*left], (*ski)) > 0) {
            ++(*left);
        }
        while (compare((*students)[*right], (*ski)) < 0) {
            --(*right);
        }
        if ((*left) <= (*right)) {
            swap((*students)[*left], (*students)[*right]);
            ++(*left);
            --(*right);
        }
    }
}

void partitionSki(vector<Ski> *skis, Student *student, int left, int right) {
    while (left <= right) {
        while (compare(*student, (*skis)[left]) < 0) {
            ++left;
        }
        while (compare(*student, (*skis)[right]) > 0) {
            --right;
        }
        if (left <= right) {
            swap((*skis)[left], (*skis)[right]);
            ++left;
            --right;
        }
    }
}

void sort(vector<Student> *students, vector<Ski> *skis, int left, int right) {
    int middle = (left + right) / 2;
    int left_ski = left, right_ski = right;
    int left_student = left, right_student = right;
    Student student = (*students)[middle];
    int temp_index = left;
    for (int index = left; index <= right; ++index) {
        if (compare(student, (*skis)[index]) == 0) {
            temp_index = index;
        }
    }
    Ski ski_pivot = (*skis)[temp_index];
    swap((*skis)[temp_index], (*skis)[middle]);

    partitionStudent(students, &ski_pivot, &left_student, &right_student);
    partitionSki(skis, &student, left_ski, right_ski);

    if (right_student > left) {
        sort(students, skis, left, right_student);
    }
    if (left_student < right) {
        sort(students, skis, left_student, right);
    }
}

void sortById(vector<Student> *students, vector<Ski> *skis, int low, int high) {
    int pivot = (*students)[(low + high) / 2].id;
    int left = low;
    int right = high;
    while (left < right) {
        while ((*students)[left].id < pivot) {
            ++left;
        }
        while ((*students)[right].id > pivot) {
            --right;
        }
        if (left <= right) {
            swap((*students)[left], (*students)[right]);
            swap((*skis)[left], (*skis)[right]);
            ++left;
            --right;
        }
    }
    if (right > low) {
        sortById(students, skis, low, right);
    }
    if (left < high) {
        sortById(students, skis, left, high);
    }
}

void findPairs(vector<Student> *students, vector<Ski> *skis) {
    // your code
    sort(students, skis, 0, students->size() - 1);
    sortById(students, skis, 0, students->size() - 1);
}
