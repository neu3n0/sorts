#pragma once
#include <functional>

namespace neu3n0 {
    class algorithms {
    public: // additional functions
        template <class T>
        static bool compareLess(const T& a, const T& b) { return !(a < b); }
        template <class T>
        static bool compareMore(const T& a, const T& b) { return !(a > b); }
        template <class RandomIt>
        static void merge(RandomIt firstBegin, RandomIt firstEnd, 
            RandomIt secondBegin, RandomIt secondEnd, RandomIt res); // merge two arrays via iterators
        template <class T>
        static void merge(T* first, size_t count1, T* second, size_t count2, T* res); // merge two arrays via pointers and size
    private: // merge for mergeSort
        template <class T>
        static void merge(T* a, size_t left, size_t middle, size_t right, std::function<bool(const T&, const T&)> compare = compareLess<T>); // merge two arrays via pointers and size
    public: // sort functions via pointer and size
        template <class T>
        static void selectionSort(T* a, size_t n, std::function<bool(const T&, const T&)> compare = compareLess<T>);
        template <class T>
        static void bubbleSort(T* a, size_t n, std::function<bool(const T&, const T&)> compare = compareLess<T>);
        template <class T>
        static void bubbleSortTwo(T* a, size_t n, std::function<bool(const T&, const T&)> compare = compareLess<T>);
        template <class T>
        static void insertionSort(T* a, size_t n, std::function<bool(const T&, const T&)> compare = compareLess<T>);
        template <class T>
        static void mergeSort(T* a, size_t left, size_t right, std::function<bool(const T&, const T&)> compare = compareLess<T>);  // [left, right)
    public: // sort functions via iterators
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
void neu3n0::algorithms::mergeSort(T* a, size_t left, size_t right, std::function<bool(const T&, const T&)> compare) {
    if (left + 1 == right) return;
    // if (left < right) return;
    size_t middle = left + (right - left) / 2;
    mergeSort(a, left, middle, compare);
    mergeSort(a, middle, right, compare);
    merge(a, left, middle, right, compare);
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