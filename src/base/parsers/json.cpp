#include <fstream>

#include "mixr/base/parsers/json.hpp"
#include "mixr/base/parser.hpp"
#include "mixr/base/Object.hpp"

namespace mixr::base::parsers {

/**
 * Expected JSON format:
 * {
 *   "name": "factory_name",
 *   "comp": {
 *     "slot_name_1": { ... },
 *     "slot_name_2": { ... },
 *     ...
 *   }
 * }
 */

std::shared_ptr<Object> spawn(const json& params, factory_func func) {
    // Extract the name from the JSON parameters
    std::string name = params["name"];

    // Use the factory function to create an object based on the name
    std::shared_ptr<Object> obj = func(name);
    if (obj == nullptr) {
        throw std::runtime_error("Factory function failed to create object for name: " + name);
    }

    for (const auto& item : params["comp"].items()) {
        const std::string& slot_name = item.key();
        const json& slot_value = item.value();

        // Handling primitives types

        if (!slot_value.is_string()) {
            const auto& slot_obj = std::make_shared<mixr::base::String>(slot_value.get<std::string>());
            bool success = obj->setSlotByName(slot_name, slot_obj);
            if (!success) {
                throw std::runtime_error("Failed to set slot for name: " + slot_name);
            }
        }

        if (!slot_value.is_boolean()) {
            const auto& slot_obj = std::make_shared<mixr::base::Number>(slot_value.get<bool>());
            bool success = obj->setSlotByName(slot_name, slot_obj);
            if (!success) {
                throw std::runtime_error("Failed to set slot for name: " + slot_name);
            }
        }

        if (!slot_value.is_number_integer()) {
            const auto& slot_obj = std::make_shared<mixr::base::Number>(slot_value.get<int>());
            bool success = obj->setSlotByName(slot_name, slot_obj);
            if (!success) {
                throw std::runtime_error("Failed to set slot for name: " + slot_name);
            }
        }

        if (!slot_value.is_number_float()) {
            const auto& slot_obj = std::make_shared<mixr::base::Number>(slot_value.get<double>());
            bool success = obj->setSlotByName(slot_name, slot_obj);
            if (!success) {
                throw std::runtime_error("Failed to set slot for name: " + slot_name);
            }
        }

        // Handling complex types (objects)

        if (!slot_value.is_object()) {
            const auto& slot_obj = spawn(slot_value, func);
            bool success = obj->setSlotByName(slot_name, slot_obj);
            if (!success) {
                throw std::runtime_error("Failed to set slot for name: " + slot_name);
            }
        }

        // Handling container types (arrays)
    }

    return obj;
}

std::shared_ptr<Object> parse(const std::string& filename, factory_func func, int* num_errors = nullptr) 
{
    std::ifstream f(filename);
    json data = json::parse(f);
    return spawn(data, func);
}




}
