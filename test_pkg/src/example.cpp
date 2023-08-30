#include <iostream>

#include "mixr/config.hpp"
#include "mixr/base/Object.hpp"

void sanity_check();

void test_mixr_base();
void test_mixr_dafif();

int main()
{
    //
    // Sanity check
    //

    sanity_check();

    //
    // mixr::base
    //

    test_mixr_base();

    return 0;
}

void sanity_check()
{
    std::cout << "Using MIXR version: "
              << MIXR_VERSION / 10000 << "."       // major version
              << MIXR_VERSION % 10000 / 100 << "." // minor version
              << MIXR_VERSION % 100                // patch level
              << std::endl;
}

void test_mixr_base()
{
    std::cout << "Testing mixr_base : ..." << std::endl;

    auto *obj = new mixr::base::Object();
    delete obj;
    obj = nullptr;

    std::cout << "Testing mixr_base : OK!" << std::endl;
}
