#include <iostream>
#include "sorts.hpp"
#include <cstring>
#include <string>

template <class T>
void printArray(const T& a, size_t n, const std::string& name = "") {
    if (!name.empty()) std::cout << name << std::endl;
    for (size_t i = 0; i < n; ++i)
        std::cout << a[i] << " ";
    std::cout << std::endl;
}

int main() {
    srand(time(nullptr));
    size_t count = 10;
    int* a = new int[count];
    for (size_t i = 0; i < count; ++i) a[i] = rand() % 20;
    int* b = new int[count];
    memcpy(b, a, count * sizeof(a[0]));
    printArray(a, count);
    std::function<bool (const int&, const int&)> cmp = 
        std::bind(neu3n0::sorts::compareMax<int>, std::placeholders::_1, std::placeholders::_2);
    
    neu3n0::sorts::selectionSort(a, count, cmp);
    printArray(a, count, "selectionSort");
    
    memcpy(a, b, count * sizeof(b[0]));
    neu3n0::sorts::bubbleSort(a, count, cmp);
    printArray(a, count, "bubbleSort");

    memcpy(a, b, count * sizeof(b[0]));
    neu3n0::sorts::bubbleSortTwo(a, count, cmp);
    printArray(a, count, "bubbleSortTwo");

    memcpy(a, b, count * sizeof(b[0]));
    neu3n0::sorts::insertionSort(a, count, cmp);
    printArray(a, count, "insertionSort");
    
    delete[] a;
    delete[] b;

    return 0;
}