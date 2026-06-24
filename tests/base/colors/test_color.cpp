#include <catch2/catch_test_macros.hpp>

#include "mixr/base/colors/Color.hpp"

using namespace mixr::base;

TEST_CASE("Color base class", "[colors]")
{
    Color color;

    REQUIRE(color.setRed(0.21));
    REQUIRE(color.setGreen(0.21));
    REQUIRE(color.setBlue(0.21));
    REQUIRE(color.setAlpha(0.21));
}
