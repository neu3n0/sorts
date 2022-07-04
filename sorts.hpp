#pragma once
#include <functional>

namespace neu3n0 {
    class sorts {
    public: // additional functions
        template <class T>
        static bool compareLess(const T& a, const T& b) { return !(a < b); }
        template <class T>
        static bool compareMore(const T& a, const T& b) { return !(a > b); }
        template <class RandomIt>
        static void merge(RandomIt firstArrayBegin, RandomIt firstArrayEnd, 
            RandomIt secondArrayBegin, RandomIt secondArrayEnd, RandomIt res); // merge two arrays via iterators
        template <class T>
        static void merge(T* first, size_t count1, T* second, size_t count2, T* res); // merge two arrays via pointers and size
    public: // sort functions via pointer and size
        template <class T>
        static void selectionSort(T* a, size_t n, std::function<bool(const T&, const T&)> compare = compareLess<T>);
        template <class T>
        static void bubbleSort(T* a, size_t n, std::function<bool(const T&, const T&)> compare = compareLess<T>);
        template <class T>
        static void bubbleSortTwo(T* a, size_t n, std::function<bool(const T&, const T&)> compare = compareLess<T>);
        template <class T>
        static void insertionSort(T* a, size_t n, std::function<bool(const T&, const T&)> compare = compareLess<T>);
    public: // sort functions via iterators
        template<class RandomIt, class Type>
        static void selectionSort(RandomIt first, RandomIt second, std::function<bool(const Type&, const Type&)> compare);
        template <class RandomIt, class Type>
        static void bubbleSort(RandomIt first, RandomIt second, std::function<bool(const Type&, const Type&)> compare);
        template <class RandomIt, class Type>
        static void bubbleSortTwo(RandomIt first, RandomIt second, std::function<bool(const Type&, const Type&)> compare);
        template <class RandomIt, class Type>
        static void insertionSort(RandomIt first, RandomIt second, std::function<bool(const Type&, const Type&)> compare);
    };
};


/*---------- sort functions via pointer and size ----------*/
template <class T>
void neu3n0::sorts::selectionSort(T* a, size_t n, std::function<bool(const T& a, const T& b)> compare) {
    for (size_t i = 0; i < n; ++i) {
        size_t t = i;
        for (size_t j = i + 1; j < n; ++j)
            if (compare(a[t], a[j])) t = j;
        if (t != i) std::swap(a[i], a[t]);
    }
}

template <class T>
void neu3n0::sorts::bubbleSort(T* a, size_t n, std::function<bool(const T& a, const T& b)> compare) {
    for (size_t i = 0; i < n - 1; ++i)
        for (size_t j = i + 1; j < n; ++j)
            if (compare(a[i], a[j])) std::swap(a[j], a[i]);
}

template <class T>
void neu3n0::sorts::bubbleSortTwo(T* a, size_t n, std::function<bool(const T& a, const T& b)> compare) {
    for (size_t i = 0; i < n - 1; ++i)
        for (size_t j = 0; j < n - 1 - i; ++j)
            if (compare(a[j], a[j + 1])) std::swap(a[j], a[j + 1]);
}

template <class T>
void neu3n0::sorts::insertionSort(T* a, size_t n, std::function<bool(const T& a, const T& b)> compare) {
    for (size_t i = 1; i < n; ++i) {
        T tmp = a[i];
        size_t j = i;
        for (; j > 0; --j) {
            if (compare(a[j - 1], tmp)) a[j] = a[j - 1];
            else break;
        }
        a[j] = tmp;
    }
}

/*---------- sort functions via iterators ----------*/

template <class RandomIt, class Type>
void neu3n0::sorts::selectionSort(RandomIt first, RandomIt second, std::function<bool(const Type& a, const Type& b)> compare) {
    size_t n = second - first;
    for (size_t i = 0; i < n; ++i) {
        size_t t = i;
        for (size_t j = i + 1; j < n; ++j)
            if (compare(first[t], first[j])) t = j;
        if (t != i) std::swap(first[i], first[t]);
    }
}

template <class RandomIt, class Type>
void neu3n0::sorts::bubbleSort(RandomIt first, RandomIt second, std::function<bool(const Type& a, const Type& b)> compare) {

}

template <class RandomIt, class Type>
void neu3n0::sorts::bubbleSortTwo(RandomIt first, RandomIt second, std::function<bool(const Type& a, const Type& b)> compare) {

}

template <class RandomIt, class Type>
void neu3n0::sorts::insertionSort(RandomIt first, RandomIt second, std::function<bool(const Type& a, const Type& b)> compare) {

}






// template <class T>
// void neu3n0::sorts::merge(T* a, T* b, T* res) {

// }