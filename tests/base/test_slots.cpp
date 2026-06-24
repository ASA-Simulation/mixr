#include <memory>

#include <catch2/catch_test_macros.hpp>

#include "mixr/base/SlotTable.hpp"

using namespace mixr::base;

TEST_CASE("No base class", "[mixr::base::SlotTable]")
{
    SlotTable table({ "slot1", "slot2", "slot3" }, nullptr);

    REQUIRE(table.index("slot1") == 1);
    REQUIRE(table.index("slot2") == 2);
    REQUIRE(table.index("slot3") == 3);
}

TEST_CASE("With empty base class", "[mixr::base::SlotTable]")
{
    auto base = std::make_shared<SlotTable>(std::vector<std::string>{}, nullptr);
    auto subclass = std::make_shared<SlotTable>(std::vector<std::string>{ "slot1", "slot2", "slot3" }, base);

    REQUIRE(subclass->index("slot1") == 1);
    REQUIRE(subclass->index("slot2") == 2);
    REQUIRE(subclass->index("slot3") == 3);
}

TEST_CASE("With full base class", "[mixr::base::SlotTable]")
{
    auto base = std::make_shared<SlotTable>(std::vector<std::string>{ "base_slot1", "base_slot2" }, nullptr);
    auto subclass = std::make_shared<SlotTable>(std::vector<std::string>{ "slot1", "slot2", "slot3" }, base);

    REQUIRE(subclass->index("base_slot1") == 1);
    REQUIRE(subclass->index("base_slot2") == 2);
    REQUIRE(subclass->index("slot1") == 3);
    REQUIRE(subclass->index("slot2") == 4);
    REQUIRE(subclass->index("slot3") == 5);
}
