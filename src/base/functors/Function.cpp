
#include "mixr/base/functors/Function.hpp"

#include "mixr/base/functors/Table.hpp"
#include "mixr/base/functors/FStorage.hpp"

#include <iostream>

namespace mixr {
namespace base {

IMPLEMENT_ABSTRACT_SUBCLASS(Function, "Function");
EMPTY_SLOTTABLE(Function);
EMPTY_COPYDATA(Function);
EMPTY_DELETEDATA(Function);

IMPLEMENT_ABSTRACT_SUBCLASS(Func1, "Func1");
EMPTY_SLOTTABLE(Func1);
EMPTY_COPYDATA(Func1);
EMPTY_DELETEDATA(Func1);

IMPLEMENT_ABSTRACT_SUBCLASS(Func2, "Func2");
EMPTY_SLOTTABLE(Func2);
EMPTY_COPYDATA(Func2);
EMPTY_DELETEDATA(Func2);

IMPLEMENT_ABSTRACT_SUBCLASS(Func3, "Func3");
EMPTY_SLOTTABLE(Func3);
EMPTY_COPYDATA(Func3);
EMPTY_DELETEDATA(Func3);

IMPLEMENT_ABSTRACT_SUBCLASS(Func4, "Func4");
EMPTY_SLOTTABLE(Func4);
EMPTY_COPYDATA(Func4);
EMPTY_DELETEDATA(Func4);

IMPLEMENT_ABSTRACT_SUBCLASS(Func5, "Func5");
EMPTY_SLOTTABLE(Func5);
EMPTY_COPYDATA(Func5);
EMPTY_DELETEDATA(Func5);

}
}
