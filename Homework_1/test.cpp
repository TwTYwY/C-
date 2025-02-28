#include "LongArithmetic.hpp"

bool testThatPlusWorksCorrectly() {
    std::cout << "Creating numbers..." << std::endl;
    LongNum a("12");
    std::cout << 'a' << std::endl;
    LongNum b("12");

    std::cout << "Performing addition..." << std::endl;
    LongNum res = a + b;

    std::cout << "Checking equality..." << std::endl;
    LongNum expected("24");

    return res == expected;
}

int main(int argc, char **argv) {
    if(testThatPlusWorksCorrectly()) {
        std::cout << "OK" << std::endl;
    } else {
        std::cout << "FAIL" << std::endl;
    }
}