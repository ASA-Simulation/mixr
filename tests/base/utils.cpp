#include "mixr/base/Object.hpp"
#include "mixr/base/macros.hpp"

/**
 * Test object
 */

class TestObject : public mixr::base::Object
{
    DECLARE_SUBCLASS(TestObject, mixr::base::Object)

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

bool fill_test_object(TestObject& obj)
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

    if (!obj.setSlotByName("val_pointer", std::make_shared<mixr::base::Object>()))
    {
        return false;
    }

    return true;
}