#pragma once

#include "mixr/base/Object.hpp"

namespace mixr {
namespace base {

//------------------------------------------------------------------------------
// class FStorage
// Description: Generic storage class for past values of function calls.
//              Use Function::storageFactory() to generate pre-ref()'d
//              FStorage objects.
//------------------------------------------------------------------------------
class FStorage : public Object
{
   DECLARE_SUBCLASS(FStorage, Object)
public:
   FStorage();
};

}
}
