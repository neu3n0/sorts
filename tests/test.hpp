#pragma once

#include "../algorithms.hpp"
#include <functional>
#include <cstring>
#include <iostream>
#include <vector>
#include <assert.h>

class tests {
public:
    static bool testViaPointer();
    static bool testViaIterator();
    static bool testMerge();
    static bool testKthInSortArray();
    static bool testNonCompareSorts();
    static bool testLongestInceSubSec();
private:
    const static size_t count{10};
    const static size_t count1{7};
    const static size_t count2{7};
    inline static std::function<bool (const double&, const double&)> cmpMore = 
        std::bind(neu3n0::algorithms::compareMore<double>, std::placeholders::_1, std::placeholders::_2);
    inline static std::function<bool (const double&, const double&)> cmpLess = 
        std::bind(neu3n0::algorithms::compareLess<double>, std::placeholders::_1, std::placeholders::_2);
    inline static bool checkFirst{false};
    inline static double tmp[10]{0};
public:
    template <class T>
    inline static void printArray(const T& a, size_t n, const std::string& name = "") {
        if (!name.empty()) std::cout << name << ":\t";
        for (size_t i = 0; i < n; ++i)
            std::cout << a[i] << " ";
        std::cout << std::endl;
    }
    template <class T, class CMP>
    inline static void checkArray(const T& a, size_t n, CMP compare, const std::string& name = "") {
        for (size_t i = 1; i < n; ++i)
            assert(compare(a[i], a[i - 1]));
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
    neu3n0::algorithms::selectionSort(a, count);
    printArray(a, count, "selectionSort");
    checkArray(a, count, cmpLess);
    
    memcpy(a, b, count * sizeof(b[0]));
    neu3n0::algorithms::bubbleSort(a, count);
    printArray(a, count, "bubbleSort");
    checkArray(a, count, cmpLess);

    memcpy(a, b, count * sizeof(b[0]));
    neu3n0::algorithms::bubbleSortTwo(a, count);
    printArray(a, count, "bubbleSortTwo");
    checkArray(a, count, cmpLess);

    memcpy(a, b, count * sizeof(b[0]));
    neu3n0::algorithms::insertionSort(a, count);
    printArray(a, count, "insertionSort");
    checkArray(a, count, cmpLess);

    memcpy(a, b, count * sizeof(b[0]));
    neu3n0::algorithms::mergeSort(a, count);
    printArray(a, count, "mergeSort");
    checkArray(a, count, cmpLess);

    memcpy(a, b, count * sizeof(b[0]));
    neu3n0::algorithms::quickSort(a, count);
    printArray(a, count, "quickSort");
    checkArray(a, count, cmpLess);

    memcpy(a, b, count * sizeof(b[0]));
    std::cout << "k = " << 3 << " : " << neu3n0::algorithms::kth(a, count - 1, 3) << std::endl;
    printArray(a, count, "kth");

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
    
    neu3n0::algorithms::selectionSort(v.begin(), v.end(), cmpLess);
    printArray(v, v.size(), "selectionSort");
    checkArray(v, v.size(), cmpLess);

    v = vTmp;
    neu3n0::algorithms::bubbleSort(v.begin(), v.end(), cmpLess);
    printArray(v, v.size(), "bubbleSort");
    checkArray(v, v.size(), cmpLess);

    v = vTmp;
    neu3n0::algorithms::bubbleSortTwo(v.begin(), v.end(), cmpLess);
    printArray(v, v.size(), "bubbleSortTwo");
    checkArray(v, v.size(), cmpLess);

    v = vTmp;
    neu3n0::algorithms::insertionSort(v.begin(), v.end(), cmpLess);
    printArray(v, v.size(), "insertionSort");
    checkArray(v, v.size(), cmpLess);

    // v = vTmp;
    // neu3n0::algorithms::mergeSort(v.begin(), v.end(), cmpLess);
    // printArray(v, v.size(), "mergeSort");

    return true;
}

bool tests::testMerge() {
    std::cout << "/*---------- merge two arrays via pointers and sizes ----------*/" << std::endl;
    double* a = new double[count1];
    double* b = new double[count2];
    double* res = new double[count1 + count2];
    for (size_t i = 0; i < count1; ++i) a[i] = rand() % 20 + static_cast<double>(rand()) / RAND_MAX;
    for (size_t i = 0; i < count2; ++i) b[i] = rand() % 20 + static_cast<double>(rand()) / RAND_MAX;
    neu3n0::algorithms::insertionSort(a, count1);
    neu3n0::algorithms::insertionSort(b, count2);
    tests::printArray(a, count1, "a");
    tests::printArray(b, count2, "b");
    neu3n0::algorithms::merge(a, count1, b, count2, res);

    tests::printArray(res, count1 + count2, "res");
    checkArray(res, count1 + count2, cmpLess);
    delete[] a;
    delete[] b;
    delete[] res; 

    std::cout << "/*---------- merge two arrays via iterators ----------*/" << std::endl;

    std::vector<double> v1(count1);
    std::vector<double> v2(count2);
    std::vector<double> vRes(count1 + count2);
    for (size_t i = 0; i < count1; ++i) v1[i] = rand() % 20 + static_cast<double>(rand()) / RAND_MAX;
    for (size_t i = 0; i < count2; ++i) v2[i] = rand() % 20 + static_cast<double>(rand()) / RAND_MAX;
    std::function<bool (const double&, const double&)> cmpLess = 
        std::bind(neu3n0::algorithms::compareLess<double>, std::placeholders::_1, std::placeholders::_2);
    neu3n0::algorithms::insertionSort(v1.begin(), v1.end(), cmpLess);
    neu3n0::algorithms::insertionSort(v2.begin(), v2.end(), cmpLess);
    tests::printArray(v1, v1.size(), "v1: ");
    tests::printArray(v2, v2.size(), "v2: ");
    neu3n0::algorithms::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), vRes.begin());
    tests::printArray(vRes, vRes.size(), "vRes: ");
    checkArray(vRes, vRes.size(), cmpLess);
    return true;
}

bool tests::testKthInSortArray() {
    std::cout << "/*---------- kth index in sort array ----------*/" << std::endl;
    double* a = new double[count];
    for (size_t i = 0; i < count; ++i) a[i] = rand() % 20 + static_cast<double>(rand()) / RAND_MAX;
    printArray(a, count);
    double x = neu3n0::algorithms::kth(a, count - 1, 4);
    neu3n0::algorithms::mergeSort(a, count);
    printArray(a, count);
    std::cout << "k = " << 4 << "   a[k] = " << x << std::endl;
    assert(x == a[4]);
    delete[] a;

    for (size_t t = 0; t < 100; ++t) {
        double* a = new double[count];
        size_t k = rand() % count;
        for (size_t i = 0; i < count; ++i) a[i] = rand() % 20 + static_cast<double>(rand()) / RAND_MAX;
        double x = neu3n0::algorithms::kth(a, count - 1, k);
        neu3n0::algorithms::mergeSort(a, count);
        assert(x == a[k]);
        delete[] a;
    }

    return true;
}

bool tests::testNonCompareSorts() {
    std::cout << "/*---------- test non compare sorts ----------*/" << std::endl;
    uint64_t* arr = new uint64_t[10];
    for (size_t i = 0; i < 10; ++i) arr[i] = rand() % 20;
    tests::printArray(arr, 10, "arr before");
    neu3n0::algorithms::countingSort(arr, 10);
    tests::printArray(arr, 10, "countingSort");
    for (size_t i = 1; i < 10; ++i)
        assert(arr[i] >= arr[i - 1]);

    for (size_t in = 0; in < 100; ++in) {
        for (size_t i = 0; i < 10; ++i) arr[i] = rand() % 20;
        neu3n0::algorithms::countingSort(arr, 10);
        for (size_t i = 1; i < 10; ++i)
            assert(arr[i] >= arr[i - 1]);
    }

    delete[] arr;
    return true;
}

bool tests::testLongestInceSubSec() {
    std::cout << "/*---------- test largest increasing subsequence ----------*/" << std::endl;

    int* a = new int[10]{2, 1, 4, 5, 2, 3, 0, 0, 0, 4};
    printArray(a, 10);
    size_t ans = neu3n0::algorithms::LIS(a, 10, true);
    std::cout << ans << std::endl;
    assert(ans == 4);
    for (size_t in = 0; in < 10; ++in) {
        for (size_t i = 0; i < 10; ++i) a[i] = rand() % 14;
        // tests::printArray(a, 10);
        neu3n0::algorithms::LIS(a, 10);
    }

    delete[] a;

    return true;
}