#include "tests/test.hpp"
#include "algorithms.hpp"
#include <assert.h>


int main() {
    srand(time(nullptr));
    
    tests::testViaPointer();
    tests::testViaIterator();
    tests::testMerge();
    return 0;
}