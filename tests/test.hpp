#pragma once

#include "../sorts.hpp"
#include <functional>
#include <cstring>
#include <iostream>
#include <vector>

class tests {
public:
    static bool testViaPointer();
    static bool testViaIterator();
private:
    const static size_t count{10};
    inline static std::function<bool (const double&, const double&)> cmpMore = 
        std::bind(neu3n0::sorts::compareMore<double>, std::placeholders::_1, std::placeholders::_2);
    inline static std::function<bool (const double&, const double&)> cmpLess = 
        std::bind(neu3n0::sorts::compareLess<double>, std::placeholders::_1, std::placeholders::_2);
    inline static bool checkFirst{false};
    inline static double tmp[10]{0};
    template <class T>
    static inline void printArray(const T& a, size_t n, const std::string& name = "") {
        if (!name.empty()) std::cout << name << std::endl;
        for (size_t i = 0; i < n; ++i)
            std::cout << a[i] << " ";
        std::cout << std::endl;
    }
};

bool tests::testViaPointer() {
    double* a = new double[count];
    for (size_t i = 0; i < count; ++i) a[i] = a[i] = rand() % 20 + static_cast<double>(rand()) / RAND_MAX;
    double* b = new double[count];
    memcpy(b, a, count * sizeof(a[0]));
    memcpy(tmp, b, count * sizeof(b[0]));

    printArray(a, count);

    std::cout << "/*---------- sort functions via pointer and size ----------*/" << std::endl;
    neu3n0::sorts::selectionSort(a, count);
    printArray(a, count, "selectionSort");
    
    memcpy(a, b, count * sizeof(b[0]));
    neu3n0::sorts::bubbleSort(a, count);
    printArray(a, count, "bubbleSort");

    memcpy(a, b, count * sizeof(b[0]));
    neu3n0::sorts::bubbleSortTwo(a, count);
    printArray(a, count, "bubbleSortTwo");

    memcpy(a, b, count * sizeof(b[0]));
    neu3n0::sorts::insertionSort(a, count);
    printArray(a, count, "insertionSort");

    memcpy(a, b, count * sizeof(b[0]));
    neu3n0::sorts::insertionSort(a, count, cmpMore);
    printArray(a, count, "insertionSortWithFunctionMore");
    
    checkFirst = true;
    delete[] a;
    delete[] b;
    
    return true;
}

bool tests::testViaIterator() {
    std::vector<double> v(count);
    if (checkFirst) 
        for (size_t i = 0; i < count; ++i) v[i] = tmp[i];
    else 
        for (size_t i = 0; i < count; ++i) v[i] = rand() % 20 + static_cast<double>(rand()) / RAND_MAX;

    std::vector<double> vTmp(v);
    printArray(v.begin(), v.size(), "");

    std::cout << "/*---------- sort functions via iterators ----------*/" << std::endl;
    
    neu3n0::sorts::selectionSort(v.begin(), v.end(), cmpLess);
    printArray(v, v.size(), "selectionSort");

    v = vTmp;
    neu3n0::sorts::bubbleSort(v.begin(), v.end(), cmpLess);
    printArray(v, v.size(), "bubbleSort");

    v = vTmp;
    neu3n0::sorts::bubbleSortTwo(v.begin(), v.end(), cmpLess);
    printArray(v, v.size(), "bubbleSortTwo");

    v = vTmp;
    neu3n0::sorts::insertionSort(v.begin(), v.end(), cmpLess);
    printArray(v, v.size(), "insertionSort");

    v = vTmp;
    neu3n0::sorts::insertionSort(v.begin(), v.end(), cmpMore);
    printArray(v, v.size(), "insertionSortWithFunctionMore");

    return true;
}