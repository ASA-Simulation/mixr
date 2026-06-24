#pragma once

#include <memory>
#include <vector>
#include <string>
#include <expected>

namespace mixr {
namespace base {

//------------------------------------------------------------------------------
// Class: SlotTable
// Description: Table of slot names (see Object.hpp)
//
// Slot tables define the names of the slots (i.e., attributes) accepted by
// the class of objects and maps these slot names to slot index numbers.
//
// The mapping of slot names and index numbers includes all base class slot
// tables that may exist.  Therefore, the first slot of the first base class
// that contains a slot table is slot number one, and the last slot in this
// table is slot N, where N is the total number of slot in this table and all
// base class tables.  See function n() below.
//
// Slot tables are usually defined using the macros BEGIN_SLOTTABLE and
// END_SLOTTABLE (see macros.hpp).
//
//------------------------------------------------------------------------------
class SlotTable
{
public:
   SlotTable() = delete;
   SlotTable(const std::vector<std::string>& slotnames, const std::shared_ptr<const SlotTable>& baseTable = nullptr);
   SlotTable(const SlotTable&) = delete;
   SlotTable& operator=(const SlotTable&) = delete;
   virtual ~SlotTable() = default;

   // Returns the last slot index number, which includes all base class slots.
   int n() const;

   // Returns the index, [ 1 .. n() ], for slot name 'slotname', or zero if not found
   int index(const std::string& slotname) const;

   // Returns the name of the slot at index 'slotindex', range [ 1 .. n() ],
   // or zero is returned if the index is out of range.
   std::expected<const std::string, std::exception> name(const int slotindex) const;

private:
   const std::shared_ptr<const SlotTable> baseTable; // Pointer to base class's slot table
   const std::vector<std::string> m_slots;             // Array of slot names
};

}
}
