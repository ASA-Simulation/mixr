#include <catch2/catch_test_macros.hpp>

#include "mixr/base/functors/Polynomial.hpp"

using namespace mixr::base;

TEST_CASE("Polynomial", "[functions]")
{
    Polynomial func;

    // Represents the polynomial f(x) = 1 + 2*x + 3*x^2
    func.setCoefficients({1.0, 2.0, 3.0}); // Set the coefficients for the polynomial

    REQUIRE(func.f(1.0) == 6.0);
    REQUIRE(func.f(10.0) == 321.0);
    REQUIRE(func.f(-10.0) == 281.0);
}
