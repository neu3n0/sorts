#include "tests/test.hpp"
#include "algorithms.hpp"
#include <assert.h>

using std::vector;
int main() {
    srand(time(nullptr));
    
    tests::testViaPointer();
    tests::testViaIterator();
    tests::testMerge();
    tests::testKthInSortArray();
    tests::testNonCompareSorts();
    tests::testLongestInceSubSec();

    return 0;
}