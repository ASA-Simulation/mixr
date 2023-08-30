
#ifndef __mixr_base_Function_H__
#define __mixr_base_Function_H__

#include "mixr/base/Object.hpp"
#include "mixr/base/safe_ptr.hpp"

namespace mixr {
namespace base {
class FStorage;
class Table;

//------------------------------------------------------------------------------
// Class: Function
//
// Description: Base for the derived, multi-dimensional function classes.
//
// Notes:
//    1) Use the storageFactory() function to create the FStorage object that
//       will maintain the previous function call values (i.e., integration).
//
//   virtual FStorage* storageFactory() const;
//       Data storage factory (pre-ref()'d)
//   virtual bool setSlotLfiTable(const Table* const msg);
//       Set Slot Tables
//
// Slots:
//    table    <Table>     ! Optional LFI table
//
//------------------------------------------------------------------------------
class Function : public Object
{
   DECLARE_SUBCLASS(Function, Object)

public:
   Function();

   virtual FStorage* storageFactory() const;    // Data storage factory (pre-ref()'d)

protected:
   const Table* getTable() const {  return table; }

private:
   safe_ptr<const Table> table;   // Optional LFI Table

protected:
   // slot table helper methods
   virtual bool setSlotLfiTable(const Table* const);
};

}
}

#endif
