#include <catch2/catch_test_macros.hpp>

#include "mixr/base/Object.hpp"
#include "mixr/base/macros.hpp"

using namespace mixr::base;

/**
 * Empty slots.
 */

class TestObject_EmptySlot : public Object
{
    DECLARE_SUBCLASS(TestObject_EmptySlot, Object)

public: 
    TestObject_EmptySlot();
};

IMPLEMENT_SUBCLASS(TestObject_EmptySlot, "TestObject_EmptySlot")
EMPTY_SLOTTABLE(TestObject_EmptySlot)
EMPTY_COPYDATA(TestObject_EmptySlot)
EMPTY_DELETEDATA(TestObject_EmptySlot)

TestObject_EmptySlot::TestObject_EmptySlot()
{
    STANDARD_CONSTRUCTOR()
}

TEST_CASE("Subclass with empty slots", "[mixr::base::Object]")
{
    TestObject_EmptySlot obj;

    REQUIRE(obj.isValid());
}

/**
 * With slots
 */

class TestObject_WithSlot : public Object
{
    DECLARE_SUBCLASS(TestObject_WithSlot, Object)

public: 
    TestObject_WithSlot();

    protected:
        bool setSlot1(std::shared_ptr<double> const) { return true; };
        bool setSlot2(std::shared_ptr<std::string> const) { return true; };
        bool setSlot3(std::shared_ptr<Object> const) { return true; };
};

IMPLEMENT_SUBCLASS(TestObject_WithSlot, "TestObject_WithSlot")
EMPTY_COPYDATA(TestObject_WithSlot)
EMPTY_DELETEDATA(TestObject_WithSlot)

BEGIN_SLOTTABLE(TestObject_WithSlot)
    "slot1",
    "slot2",
    "slot3",
END_SLOTTABLE(TestObject_WithSlot)

BEGIN_SLOT_MAP(TestObject_WithSlot)
    ON_SLOT_REAL(1, setSlot1)
    ON_SLOT_STRING(2, setSlot2)
    ON_SLOT_OBJECT(3, setSlot3, Object)
END_SLOT_MAP()

TestObject_WithSlot::TestObject_WithSlot()
{
    STANDARD_CONSTRUCTOR()
}

TEST_CASE("Subclass with some slots", "[mixr::base::Object]")
{
    TestObject_WithSlot obj;

    REQUIRE(obj.isValid());

    REQUIRE(obj.getSlotTable()->n() == 3);

    REQUIRE(obj.setSlotByName("slot1", std::make_shared<double>(3.14)));
    REQUIRE(obj.setSlotByName("slot2", std::make_shared<std::string>("PI")));
    REQUIRE(obj.setSlotByName("slot3", std::make_shared<Object>()));

    REQUIRE_FALSE(obj.setSlotByName("slot1", std::make_shared<std::string>("PI")));
    REQUIRE_FALSE(obj.setSlotByName("slot2", std::make_shared<Object>()));
    REQUIRE_FALSE(obj.setSlotByName("slot3", std::make_shared<double>(3.14)));
}


