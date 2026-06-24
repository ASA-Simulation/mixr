#pragma once

#include <string>
#include <memory>

// #include "mixr/base/numeric/Boolean.hpp"
// #include "mixr/base/numeric/Float.hpp"
// #include "mixr/base/numeric/Integer.hpp"
// #include "mixr/base/String.hpp"

namespace mixr {
namespace base {

class Object;



//
// factory function signature (e.g., factory(const std::string& name); )
// -- the user defines this function
//
using factory_func = std::shared_ptr<Object> (*)(const std::string& name);

//
// edl_parser( text filename to parse, user supplied factory function to create objects,
//             pointer to variable for num of errors found )
//
extern std::shared_ptr<Object> parse(const std::string& filename, factory_func f, int* num_errors = nullptr);

std::shared_ptr<Object> empty_factory(const std::string& name)
{
    return nullptr;
}

std::shared_ptr<Object> primitives_factory(const std::string& name)
{
    // if (name == "boolean") {
    //     return std::make_shared<Boolean>();
    // }

    // if (name == "float") {
    //     return std::make_shared<Float>();
    // }

    // if (name == "int") {
    //     return std::make_shared<Integer>();
    // }

    // if (name == "string") {
    //     return std::make_shared<String>();
    // }

    return nullptr;
}

}
}
