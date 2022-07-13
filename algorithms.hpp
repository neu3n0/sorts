#pragma once
#include <functional>
#include <iostream>
#include <utility>
#include <vector>
#include <utility>

namespace neu3n0 {
    class algorithms {
    public: // additional functions
        template <class T>
        static bool compareLess(const T& a, const T& b) { return !(a < b); }
        template <class T>
        static bool compareMore(const T& a, const T& b) { return !(a > b); }

    private: // merge for mergeSort
        template <class T>
        static void merge(T* a, size_t left, size_t middle, size_t right, std::function<bool(const T&, const T&)> compare = compareLess<T>); // merge two arrays via pointers and size
        // template <class RandomIt, class Type>
        // static void merge(RandomIt left, RandomIt middle, RandomIt right, std::function<bool(const Type&, const Type&)> compare); // merge two arrays via iterators

    public: 
        // sort functions via pointer and size
        template <class T>
        static void selectionSort(T* a, size_t n, std::function<bool(const T&, const T&)> compare = compareLess<T>);
        template <class T>
        static void bubbleSort(T* a, size_t n, std::function<bool(const T&, const T&)> compare = compareLess<T>);
        template <class T>
        static void bubbleSortTwo(T* a, size_t n, std::function<bool(const T&, const T&)> compare = compareLess<T>);
        template <class T>
        static void insertionSort(T* a, size_t n, std::function<bool(const T&, const T&)> compare = compareLess<T>);
        template <class T>
        static void mergeSort(T* a, size_t right, std::function<bool(const T&, const T&)> compare = compareLess<T>, size_t left = 0);  // [left, right)
        template <class T>
        static void quickSort(T* a, size_t right, std::function<bool(const T&, const T&)> compare = compareLess<T>, size_t left = 0);  // [left, right) 
        static void countingSort(uint64_t* a, size_t n);  // [left, right) 
        static void digitalSort(std::vector<std::pair<uint64_t, uint64_t>>& a);

        // sort functions via iterators
        template<class RandomIt, class Type>
        static void selectionSort(RandomIt first, RandomIt second, std::function<bool(const Type&, const Type&)> compare);
        template <class RandomIt, class Type>
        static void bubbleSort(RandomIt first, RandomIt second, std::function<bool(const Type&, const Type&)> compare);
        template <class RandomIt, class Type>
        static void bubbleSortTwo(RandomIt first, RandomIt second, std::function<bool(const Type&, const Type&)> compare);
        template <class RandomIt, class Type>
        static void insertionSort(RandomIt first, RandomIt second, std::function<bool(const Type&, const Type&)> compare);
        // template <class RandomIt, class Type>
        // static void mergeSort(RandomIt first, RandomIt second, std::function<bool(const Type&, const Type&)> compare);
        // template <class RandomIt, class Type>
        // static void quickSort(RandomIt first, RandomIt second, std::function<bool(const Type&, const Type&)> compare);

    public:
        // merge two arrays
        template <class T>
        static void merge(T* first, size_t count1, T* second, size_t count2, T* res);
        template <class RandomIt>
        static void merge(RandomIt firstBegin, RandomIt firstEnd, RandomIt secondBegin, RandomIt secondEnd, RandomIt res);
        
        // find element on k pos after sort
        template <class T>
        static T kth(T* a, size_t right, size_t k, std::function<bool(const T&, const T&)> compare = compareLess<T>, size_t left = 0); // [left, right)

        // largest increasing subsequence
        template<class T>
        static size_t LIS(T* arr, size_t n, bool check = false);

        // fib num
        static uint64_t fib(uint64_t n);
        // pow
        static int64_t pow(int64_t a, int64_t n);
    };
};


/*---------- sort functions via pointer and size ----------*/
template <class T>
void neu3n0::algorithms::selectionSort(T* a, size_t n, std::function<bool(const T& a, const T& b)> compare) {
    for (size_t i = 0; i < n; ++i) {
        size_t t = i;
        for (size_t j = i + 1; j < n; ++j)
            if (compare(a[t], a[j])) t = j;
        if (t != i) std::swap(a[i], a[t]);
    }
}

template <class T>
void neu3n0::algorithms::bubbleSort(T* a, size_t n, std::function<bool(const T& a, const T& b)> compare) {
    for (size_t i = 0; i < n - 1; ++i)
        for (size_t j = i + 1; j < n; ++j)
            if (compare(a[i], a[j])) std::swap(a[i], a[j]);
}

template <class T>
void neu3n0::algorithms::bubbleSortTwo(T* a, size_t n, std::function<bool(const T& a, const T& b)> compare) {
    for (size_t i = 0; i < n - 1; ++i)
        for (size_t j = 0; j < n - 1 - i; ++j)
            if (compare(a[j], a[j + 1])) std::swap(a[j], a[j + 1]);
}

template <class T>
void neu3n0::algorithms::insertionSort(T* a, size_t n, std::function<bool(const T& a, const T& b)> compare) {
    for (size_t i = 1; i < n; ++i) {
        T tmp = a[i];
        size_t j = i;
        for (; j > 0; --j) {
            if (compare(a[j - 1], tmp)) a[j] = a[j - 1];
            else break;
        }
        if (j != i) a[j] = tmp;
    }
}

template <class T>
void neu3n0::algorithms::mergeSort(T* a, size_t right, std::function<bool(const T&, const T&)> compare, size_t left) {
    if (left + 1 == right) return;
    size_t middle = left + (right - left) / 2;
    mergeSort(a, middle, compare, left);
    mergeSort(a, right, compare, middle);
    merge(a, left, middle, right, compare);
}

template <class T>
void neu3n0::algorithms::quickSort(T* a, size_t right, std::function<bool(const T&, const T&)> compare, size_t left) {
    if (left >= right) return;
    size_t i = left + 1;
    // size_t j = right;

    // [0, n) not [0, n - 1)
    size_t j = right - 1;
    if (i > j) return;

    while (i < j) {
        // if (a[i] < a[left]) ++i;
        if (compare(a[left], a[i])) ++i;
        else {
            std::swap(a[i], a[j]);
            --j;
        }
    }
    if (a[left] <= a[i]) --i;
    std::swap(a[left], a[i]);
    quickSort(a, i, compare, left);
    quickSort(a, right, compare, i + 1);
}

void neu3n0::algorithms::countingSort(uint64_t* a, size_t n) {
    if (n < 1) return;
    uint64_t maxNum = a[0];
    for (size_t i = 1; i < n; ++i)
        if (a[i] > maxNum)
            maxNum = a[i];
    uint64_t* b = new uint64_t[maxNum + 1];
    for (size_t i = 0; i <= maxNum; ++i) b[i] = 0;
    for (size_t i = 0; i < n; ++i)
        b[a[i]]++;
    size_t p = 0;
    for (size_t i = 0; i <= maxNum; ++i) {
        for (size_t j = 0; j < b[i]; ++j) {
            a[p] = i;
            ++p;
        }
    }
    if (p != n) std::cout << "?\n"; 
    delete[] b;
}

void neu3n0::algorithms::digitalSort(std::vector<std::pair<uint64_t, uint64_t>>& a) {
    using pairUInt = std::pair<uint64_t, uint64_t>;
    
}

/*---------- sort functions via iterators ----------*/

template <class RandomIt, class Type>
void neu3n0::algorithms::selectionSort(RandomIt first, RandomIt second, std::function<bool(const Type& a, const Type& b)> compare) {
    size_t n = second - first;
    for (size_t i = 0; i < n; ++i) {
        size_t t = i;
        for (size_t j = i + 1; j < n; ++j)
            if (compare(first[t], first[j])) t = j;
        if (t != i) std::swap(first[i], first[t]);
    }
}

template <class RandomIt, class Type>
void neu3n0::algorithms::bubbleSort(RandomIt first, RandomIt second, std::function<bool(const Type& a, const Type& b)> compare) {
    size_t n = second - first;
    for (size_t i = 0; i < n - 1; ++i)
        for (size_t j = i + 1; j < n; ++j)
            if (compare(first[i], first[j])) std::swap(first[i], first[j]);
}

template <class RandomIt, class Type>
void neu3n0::algorithms::bubbleSortTwo(RandomIt first, RandomIt second, std::function<bool(const Type& a, const Type& b)> compare) {
    size_t n = second - first;
    for (size_t i = 0; i < n - 1; ++i)
        for (size_t j = 0; j < n - i - 1; ++j)
            if (compare(first[j], first[j + 1])) std::swap(first[j], first[j + 1]);
}

template <class RandomIt, class Type>
void neu3n0::algorithms::insertionSort(RandomIt first, RandomIt second, std::function<bool(const Type& a, const Type& b)> compare) {
    size_t n = second - first;
    for (size_t i = 0; i < n; ++i) {
        size_t j = i;
        auto tmp = first[i];
        for (; j > 0; --j) {
            if (compare(first[j - 1], tmp)) first[j] = first[j - 1];
            else break;
        }
        if (j != i) first[j] = tmp;
    }
}

// template <class RandomIt, class Type>
// void neu3n0::algorithms::mergeSort(RandomIt first, RandomIt second, std::function<bool(const Type& a, const Type& b)> compare) {
//     if ((second - first) == 1) return;
//     size_t middle = (second - first) / 2;
//     mergeSort(first, first + middle, compare);
//     mergeSort(first + middle, second);
//     merge(first, first + middle, second, compare);
// }

/*---------- merge via pointers and size ----------*/

template <class T>
void neu3n0::algorithms::merge(T* first, size_t count1, T* second, size_t count2, T* res) {
    size_t i = 0, j = 0, p = 0;
    while (i < count1 && j < count2) {
        if (first[i] < second[j]) {
            res[p] = first[i];
            ++i;
        }
        else {
            res[p] = second[j];
            ++j;
        }
        ++p;
    }
    while (i < count1) {
        res[p] = first[i];
        ++i;
        ++p;
    }
    while (j < count2) {
        res[p] = second[j];
        ++j;
        ++p;
    }
}

template <class T>
void neu3n0::algorithms::merge(T* a, size_t left, size_t middle, size_t right, std::function<bool(const T&, const T&)> compare) {
    size_t i = left, j = middle, p = 0;
    T* res = new T[right - left];
    while (i < middle && j < right) {
        if (compare(a[j], a[i])) {
            res[p] = a[i];
            ++i;
        }
        else {
            res[p] = a[j];
            ++j;
        }
        ++p;
    }
    while (i < middle) {
        res[p] = a[i];
        ++i;
        ++p;
    }
    while (j < right) {
        res[p] = a[j];
        ++j;
        ++p;
    }

    for (size_t in = 0; in < right - left; ++in) a[left + in] = res[in];
    delete[] res;
}

/*---------- merge via iterators ----------*/

template <class RandomIt>
void neu3n0::algorithms::merge(RandomIt firstBegin, RandomIt firstEnd, RandomIt secondBegin, RandomIt secondEnd, RandomIt res) {
    size_t count1 = firstEnd - firstBegin;
    size_t count2 = secondEnd - secondBegin;
    size_t i = 0, j = 0, p = 0;
    while (i < count1 && j < count2) {
        if (firstBegin[i] < secondBegin[j]) {
            res[p] = firstBegin[i];
            ++i;
        }
        else {
            res[p] = secondBegin[j];
            ++j;
        }
        ++p;
    }
    while (i < count1) {
        res[p] = firstBegin[i];
        ++i;
        ++p;
    }
    while (j < count2) {
        res[p] = secondBegin[j];
        ++j;
        ++p;
    }    
}

// template <class RandomIt, class Type>
// void neu3n0::algorithms::merge(RandomIt left, RandomIt middle, RandomIt right, std::function<bool(const Type&, const Type&)> compare) {
//     size_t i = 0, j = 0, p = 0;
//     Type* res = new Type[right - left];
//     while (i < (middle - left) && j < (right - middle)) {
//         if (compare(left[i], middle[j])) {
//             res[p] = left[i];
//             ++i;
//         }
//         else {
//             res[p] = middle[i];
//             ++i;
//         }
//         ++p;
//     }
//     while (i < (middle - left)) {
//         res[p] = left[i];
//         ++i;
//         ++p;
//     }
//     while (j < (right - middle)) {
//         res[p] = middle[j];
//         ++j;
//         ++p;
//     }

//     for (size_t in = 0; in < right - left; ++in) left[in] = res[in];
//     delete[] res;
// }

/*---------- find element on k pos after sort ----------*/
template <class T>
T neu3n0::algorithms::kth(T* a, size_t right, size_t k, std::function<bool(const T&, const T&)> compare, size_t left) {
    if (left >= right) return a[left]; 
    size_t i = left + 1;
    size_t j = right;

    while (i < j) {
        if (compare(a[left], a[i])) ++i;
        else {
            std::swap(a[i], a[j]);
            --j;
        }
    }
    if (a[left] <= a[i]) --i;
    std::swap(a[left], a[i]);
    if (k < i - left) return kth(a, i - 1, k, compare, left);
    else if (k == i - left) return a[k + left];
    else return kth(a, right, k - (i - left + 1), compare, i + 1);
}

template <class T>
size_t neu3n0::algorithms::LIS(T* a, size_t n, bool check) {
    int* f = new int[n];
    int* p = new int[n];
    for (size_t i = 0; i < n; ++i) {
        f[i] = 1;
        for (size_t j = 0; j < i; ++j)
            if (a[i] > a[j]) {
                if (f[i] < f[j] + 1) {
                    f[i] = f[j] + 1;
                    p[i] = j;
                }
                // f[i] = std::max(std::max(f[i], f[j] + 1), 1);   if we need sequence --> not max --> if () {} --> and save way
            }
    }
    int ans = 0;
    size_t ind = 0;
    for (size_t i = 0; i < n; ++i)
        if (f[i] > ans) {
            ans = f[i];
            ind = i;
        }
        // ans = std::max(ans, f[i]); if we ...

    if (check) {
        for (size_t i = 0; i < ans; ++i) {
            std::cout << a[ind] << " ";
            ind = p[ind];
        }
        std::cout << std::endl;    
    }
    
            
    delete[] f;

    return ans;
}

uint64_t neu3n0::algorithms::fib(uint64_t n) {
    if (n == 1 || n == 2) return 1;
    return fib(n - 1) + fib(n - 2);
}

int64_t pow(int64_t a, int64_t n) {
    // a^n = a^k * a^k = a^(2k); n - четное, 
    // a^n = a^(2k) * a = a^(2k+1); n - нечетное
    if (n == 0) return 1;
    
    // O(n)
    // int b = pow(a, n / 2) * pow(a, n / 2);
    
    // O(logn)
    int64_t b = pow(a, n / 2);
    b *= b;

    if (n % 2 == 1) b *= a;
    return b;
}