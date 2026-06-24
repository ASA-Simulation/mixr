#pragma once

#include <string>

namespace mixr {
namespace base { class Object; }
namespace terrain {
base::Object* factory(const std::string&);
}

}

