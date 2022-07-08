#include <iostream>

// a^n = a^k * a^k = a^(2k); n - четное
// a^n = a^(2k) * a = a^(2k+1); n - нечетное

int64_t pow(int64_t a, int64_t n) {
    if (n == 0) return 1;
    // O(n)
    // int b = pow(a, n / 2) * pow(a, n / 2);

    // O(logn)
    int64_t b = pow(a, n / 2);
    b *= b;

    if (n % 2 == 1) b *= a;
    return b;
}

int main() {
    int64_t a, n;
    std::cin >> a >> n;
    std::cout << pow(a, n) << std::endl;
    return 0;
}