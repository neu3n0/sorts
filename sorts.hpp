#include <functional>

namespace neu3n0 {
    class sorts {
    public:
        template <class T>
        static bool compareMin(const T& a, const T& b) { return a < b; }
        template <class T>
        static bool compareMax(const T& a, const T& b) { return a > b; }
        template <class T>
        static void selectionSort(T* a, size_t n, std::function<bool(const T&, const T&)> compare);
        template <class T>
        static void bubbleSort(T* a, size_t n, std::function<bool(const T&, const T&)> compare);
        template <class T>
        static void bubbleSortTwo(T* a, size_t n, std::function<bool(const T&, const T&)> compare);
        template <class T>
        static void insertionSort(T* a, size_t n, std::function<bool(const T&, const T&)> compare);
    };
};

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