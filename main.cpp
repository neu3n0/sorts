#include "tests/test.hpp"
#include "sorts.hpp"

int main() {
    srand(time(nullptr));
    
    tests::testViaPointer();
    tests::testViaIterator();

    return 0;
}