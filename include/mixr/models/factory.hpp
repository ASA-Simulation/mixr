#pragma once

#include <string>

namespace mixr {
namespace base { class Object; }
namespace models {
base::Object* factory(const std::string&);
}

}

