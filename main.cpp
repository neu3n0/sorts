#include "tests/test.hpp"
#include "algorithms.hpp"

int main() {
    srand(time(nullptr));
    
    tests::testViaPointer();
    tests::testViaIterator();
    tests::testMerge();    
    
    return 0;
}