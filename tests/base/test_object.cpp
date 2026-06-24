#include <catch2/catch_test_macros.hpp>

#include "mixr/base/Object.hpp"

using namespace mixr::base;

TEST_CASE("Simple", "[mixr::base::Object]")
{
    Object obj;

    REQUIRE(obj.isValid());
}

/**
 * Test object
 */

class TestObject : public Object
{
    DECLARE_SUBCLASS(TestObject, Object)

public: 
    TestObject() = default;

protected:
    bool setSlotValBoolean(std::shared_ptr<bool> const val) { val_bool = *val; return true; };
    bool setSlotValDouble(std::shared_ptr<double> const val) { val_double = *val; return true; };
    bool setSlotValString(std::shared_ptr<std::string> const val) { val_string = *val; return true; };
    bool setSlotValPointer(std::shared_ptr<Object> const val) { val_pointer = val; return true; };

    std::shared_ptr<bool> getSlotValBoolean() const { return std::make_shared<bool>(val_bool); };
    std::shared_ptr<double> getSlotValDouble() const { return std::make_shared<double>(val_double); };
    std::shared_ptr<std::string> getSlotValString() const { return std::make_shared<std::string>(val_string); };
    std::shared_ptr<Object> getSlotValPointer() const { return val_pointer; };

public:
    // Member attributes are public JUST for testing
    double val_bool{false};
    double val_double{0.0};
    std::string val_string{""};
    std::shared_ptr<Object> val_pointer{nullptr};
};

IMPLEMENT_SUBCLASS(TestObject, "TestObject")

BEGIN_SLOTTABLE(TestObject)
    "val_bool",
    "val_double",
    "val_string",
    "val_pointer",
END_SLOTTABLE(TestObject)

BEGIN_SLOT_GETTER_MAP(TestObject)
    GET_SLOT(1, getSlotValBoolean)
    GET_SLOT(2, getSlotValDouble)
    GET_SLOT(3, getSlotValString)
    GET_SLOT(4, getSlotValPointer)
END_SLOT_GETTER_MAP()

BEGIN_SLOT_SETTER_MAP(TestObject)
    ON_SLOT_BOOL(1, setSlotValBoolean)
    ON_SLOT_REAL(2, setSlotValDouble)
    ON_SLOT_STRING(3, setSlotValString)
    ON_SLOT_OBJECT(4, setSlotValPointer, Object)
END_SLOT_SETTER_MAP()

bool fill_object(TestObject& obj)
{
    if (!obj.setSlotByName("val_bool", std::make_shared<bool>(true)))
    {
        return false;
    }

    if (!obj.setSlotByName("val_double", std::make_shared<double>(3.14)))
    {
        return false;
    }

    if (!obj.setSlotByName("val_string", std::make_shared<std::string>("pi")))
    {
        return false;
    }

    if (!obj.setSlotByName("val_pointer", std::make_shared<Object>()))
    {
        return false;
    }

    return true;
}

TEST_CASE("Copy constructor with state", "[mixr::base::Object]")
{
    TestObject obj1;

    REQUIRE(obj1.setSlotByName("val_bool", std::make_shared<bool>(true)));
    REQUIRE(obj1.val_bool == true);

    REQUIRE(obj1.setSlotByName("val_double", std::make_shared<double>(3.14)));
    REQUIRE(obj1.val_double == 3.14);

    REQUIRE(obj1.setSlotByName("val_string", std::make_shared<std::string>("pi")));
    REQUIRE(obj1.val_string == "pi");

    REQUIRE(obj1.setSlotByName("val_pointer", std::make_shared<Object>()));
    REQUIRE(obj1.val_pointer != nullptr);

    TestObject obj2(obj1);
    REQUIRE(obj1.val_bool == obj2.val_bool);
    REQUIRE(obj1.val_double == obj2.val_double);
    REQUIRE(obj1.val_string == obj2.val_string);
    REQUIRE(obj1.val_pointer == obj2.val_pointer);
}

TEST_CASE("Copy operator with state", "[mixr::base::Object]")
{
    TestObject obj1;

    REQUIRE(obj1.setSlotByName("val_bool", std::make_shared<bool>(true)));
    REQUIRE(obj1.val_bool == true);

    REQUIRE(obj1.setSlotByName("val_double", std::make_shared<double>(3.14)));
    REQUIRE(obj1.val_double == 3.14);

    REQUIRE(obj1.setSlotByName("val_string", std::make_shared<std::string>("pi")));
    REQUIRE(obj1.val_string == "pi");

    REQUIRE(obj1.setSlotByName("val_pointer", std::make_shared<Object>()));
    REQUIRE(obj1.val_pointer != nullptr);

    TestObject obj2 = obj1;
    REQUIRE(obj1.val_bool == obj2.val_bool);
    REQUIRE(obj1.val_double == obj2.val_double);
    REQUIRE(obj1.val_string == obj2.val_string);
    REQUIRE(obj1.val_pointer == obj2.val_pointer);
}


TEST_CASE("Getters", "[mixr::base::Object]")
{
    TestObject obj;
    REQUIRE(fill_object(obj));

    const auto& slot =  obj.getSlotByName("val_bool");
    const auto& val =  std::get<std::shared_ptr<bool>>(slot);
    REQUIRE(*val == true);
}

// TEST_CASE("Serializer", "[mixr::base::Object]")
// {
//     TestObject obj;
//     REQUIRE(fill_object(obj));
//
//     const auto& table = obj.getSlotTable();
//     for (int i = 1; i <= table->n(); i++)
//     {
//         const auto& name = table->name(i);
//         const auto& elem = obj.getSlotByName(name);
//         std::
//     }
//
//     const auto& slot =  std::get<std::shared_ptr<bool>>(obj.getSlotByName("val_bool"));
//     REQUIRE(*slot == true);
// }
