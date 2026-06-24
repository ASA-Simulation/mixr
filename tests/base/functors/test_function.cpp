#include <vector>

#include <catch2/catch_test_macros.hpp>

#include "mixr/base/functors/Function.hpp"

using namespace mixr::base;

//
// Testing Func1
//

class TestFunc1 : public Func1
{
    DECLARE_SUBCLASS(TestFunc1, Func1)
public:
    TestFunc1() = default;  

    virtual double f(const double iv1) const {
        return iv1;
    };
};

IMPLEMENT_ABSTRACT_SUBCLASS(TestFunc1, "TestFunc1");
EMPTY_SLOTTABLE(TestFunc1);
EMPTY_COPYDATA(TestFunc1);
EMPTY_DELETEDATA(TestFunc1);

TEST_CASE("TestFunc1", "[functions]")
{
    TestFunc1 func;

    REQUIRE(func.f(1.0) == 1.0);

    std::vector<double> result = func.map(std::vector<double>{1.0});
    REQUIRE(result.size() == 1);
    REQUIRE(result[0] == 1.0);
}

//
// Testing Func2
//

class TestFunc2 : public Func2
{
    DECLARE_SUBCLASS(TestFunc2, Func2)
public:
    TestFunc2() = default;

    virtual double f(const double iv1, const double iv2) const {
        return iv1 + iv2;
    };
};

IMPLEMENT_ABSTRACT_SUBCLASS(TestFunc2, "TestFunc2");
EMPTY_SLOTTABLE(TestFunc2);
EMPTY_COPYDATA(TestFunc2);
EMPTY_DELETEDATA(TestFunc2);

TEST_CASE("TestFunc2", "[functions]")
{
    TestFunc2 func;

    REQUIRE(func.f(1.0, 2.0) == 3.0);

    std::vector<double> result = func.map(std::vector<double>{1.0, 2.0});
    REQUIRE(result.size() == 1);
    REQUIRE(result[0] == 3.0);
}

//
// Testing Func3
//

class TestFunc3 : public Func3
{
    DECLARE_SUBCLASS(TestFunc3, Func3)
public:
    TestFunc3() = default;

    virtual double f(const double iv1, const double iv2, const double iv3) const {
        return iv1 + iv2 + iv3;
    };
};

IMPLEMENT_ABSTRACT_SUBCLASS(TestFunc3, "TestFunc3");
EMPTY_SLOTTABLE(TestFunc3);
EMPTY_COPYDATA(TestFunc3);
EMPTY_DELETEDATA(TestFunc3);

TEST_CASE("TestFunc3", "[functions]")
{
    TestFunc3 func;

    REQUIRE(func.f(1.0, 2.0, 3.0) == 6.0);
    
    std::vector<double> result = func.map(std::vector<double>{1.0, 2.0, 3.0});
    REQUIRE(result.size() == 1);
    REQUIRE(result[0] == 6.0);
}

//
// Testing Func4
//

class TestFunc4 : public Func4
{
    DECLARE_SUBCLASS(TestFunc4, Func4)
public:
    TestFunc4() = default;

    virtual double f(const double iv1, const double iv2, const double iv3, const double iv4) const {
        return iv1 + iv2 + iv3 + iv4;
    };
};

IMPLEMENT_ABSTRACT_SUBCLASS(TestFunc4, "TestFunc4");
EMPTY_SLOTTABLE(TestFunc4);
EMPTY_COPYDATA(TestFunc4);
EMPTY_DELETEDATA(TestFunc4);

TEST_CASE("TestFunc4", "[functions]")
{
    TestFunc4 func;

    REQUIRE(func.f(1.0, 2.0, 3.0, 4.0) == 10.0);

    std::vector<double> result = func.map(std::vector<double>{1.0, 2.0, 3.0, 4.0});
    REQUIRE(result.size() == 1);
    REQUIRE(result[0] == 10.0);
}

//
// Testing Func5
//

class TestFunc5 : public Func5
{
    DECLARE_SUBCLASS(TestFunc5, Func5)
public:
    TestFunc5() = default;

    virtual double f(const double iv1, const double iv2, const double iv3, const double iv4, const double iv5) const {
        return iv1 + iv2 + iv3 + iv4 + iv5;
    };
};

IMPLEMENT_ABSTRACT_SUBCLASS(TestFunc5, "TestFunc5");
EMPTY_SLOTTABLE(TestFunc5);
EMPTY_COPYDATA(TestFunc5);
EMPTY_DELETEDATA(TestFunc5);

TEST_CASE("TestFunc5", "[functions]")
{
    TestFunc5 func;

    REQUIRE(func.f(1.0, 2.0, 3.0, 4.0, 5.0) == 15.0);

    std::vector<double> result = func.map(std::vector<double>{1.0, 2.0, 3.0, 4.0, 5.0});
    REQUIRE(result.size() == 1);
    REQUIRE(result[0] == 15.0);
}
