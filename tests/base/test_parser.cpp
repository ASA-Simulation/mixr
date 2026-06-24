#include <catch2/catch_test_macros.hpp>
#include <nlohmann/json.hpp>

#include "mixr/base/parser.hpp"
#include "mixr/base/parsers/json.hpp"

#include "utils.cpp"

using namespace mixr::base;

using json = nlohmann::json;

TEST_CASE("Primitive types: Object", "[parser]")
{
    json answer = R"(
        {
            "name": "Object",
            "comp": {}
        }
    )"_json;

    json wrong = R"(
        {
            "name": "Not the name",
            "comp": {}
        }
    )"_json;

    const auto& obj = std::make_shared<Object>();
    REQUIRE(mixr::base::parsers::serialize(obj) == answer);
    REQUIRE(mixr::base::parsers::serialize(obj) != wrong);
}

TEST_CASE("Complex types: Object", "[parser]")
{
    json answer = R"(
        {
            "name": "TestObject",
            "comp": {
                "val_bool": true,
                "val_double": 3.14,
                "val_pointer": {
                    "name": "Object",
                    "comp": {}
                },
                "val_string": "pi"
            }
        }
    )"_json;

    const auto& obj = std::make_shared<TestObject>();
    fill_test_object(*obj);
    REQUIRE(mixr::base::parsers::serialize(obj) == answer);
}
