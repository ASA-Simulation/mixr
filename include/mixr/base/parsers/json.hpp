#pragma once

#include <nlohmann/json.hpp>

#include "mixr/base/Object.hpp"

using json = nlohmann::json;

namespace mixr::base::parsers {

std::shared_ptr<Object> spawn(const json& params, factory_func func);

std::shared_ptr<Object> parse(const std::string& filename, factory_func func, int* num_errors = nullptr);

json serialize_object(const Object& obj);

json serialize(const Element& elem)
{
    if (std::holds_alternative<nullptr_t>(elem))
    {
        return json(nullptr);
    }
    else if (std::holds_alternative<std::shared_ptr<bool>>(elem))
    {
        const auto& val = std::get<std::shared_ptr<bool>>(elem);
        return json(*val);
    }
    else if (std::holds_alternative<std::shared_ptr<double>>(elem))
    {
        const auto& val = std::get<std::shared_ptr<double>>(elem);
        return json(*val);
    }
    else if (std::holds_alternative<std::shared_ptr<std::string>>(elem))
    {
        const auto& val = std::get<std::shared_ptr<std::string>>(elem);
        return json(*val);
    }
    else if (std::holds_alternative<std::shared_ptr<Object>>(elem))
    {
        const auto& val = std::get<std::shared_ptr<Object>>(elem);
        return serialize_object(*val);
    }

    return json(nullptr);
}

json serialize_object(const Object& obj)
{
    json payload = R"(
        {
            "name": "",
            "comp": {}
        }
    )"_json;

    payload["name"] = obj.getMetaObject()->getFactoryName();

    const auto& table = obj.getSlotTable();
    for (int i = 1; i <= table->n(); i++)
    {
        const auto& name = table->name(i).value();
        const auto& elem = obj.getSlotByName(name);
        payload["comp"].emplace(name, serialize(elem));
    }

    return payload;
}

}
