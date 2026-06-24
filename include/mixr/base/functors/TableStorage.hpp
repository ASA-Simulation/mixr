#pragma once

#include "mixr/base/functors/FStorage.hpp"

namespace mixr::base {

//------------------------------------------------------------------------------
// Class: TableStorage
//------------------------------------------------------------------------------
class TableStorage : public FStorage
{
   DECLARE_SUBCLASS(TableStorage, FStorage)

public:
   TableStorage();
   unsigned int xbp{}, ybp{}, zbp{}, wbp{}, vbp{};
};

}
