#include <iostream>

// 1 1 2 3 5 8 13 21

// a(i) = a(i - 1) + a(i - 2);

uint64_t fib(uint64_t n) {
    if (n == 1 || n == 2) return 1;
    return fib(n - 1) + fib(n - 2);
}

int main() {
    uint64_t n;
    std::cin >> n;
    for (size_t i = 1; i < n; ++i)
        std::cout << i << ": " << fib(i) << std::endl;
    return 0;
}