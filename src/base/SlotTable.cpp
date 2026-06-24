
#include "mixr/base/SlotTable.hpp"
#include <cstring>

namespace mixr {
namespace base {

SlotTable::SlotTable(const std::vector<std::string>& slots, const std::shared_ptr<const SlotTable>& base) : baseTable(base), m_slots(slots)
{
}

//------------------------------------------------------------------------------
// n() -- returns the number of slots
//------------------------------------------------------------------------------
int SlotTable::n() const
{
   if (baseTable != nullptr)
      return baseTable->n() + m_slots.size();
   else
      return m_slots.size();
}

//------------------------------------------------------------------------------
// name() -- returns the name of the slot at index 'slotindex'
//------------------------------------------------------------------------------
std::expected<const std::string, std::exception> SlotTable::name(const int slotindex) const
{
   // early out if it's not between 1 .. n()
   if (slotindex == 0 || slotindex > n()) {
      return std::unexpected(std::out_of_range("SlotTable::name(slotindex) -- slotindex is out of range"));
   }

   std::string name {""};

   // check base table first
   if (baseTable != nullptr) name = baseTable->name(slotindex).value_or("");

   // if not in baseTable, check our table
   if (name == "") {
      int i = static_cast<int>(slotindex);            // a) start with slotindex
      if (baseTable != nullptr) i -= baseTable->n();  // b) subt baseTable->n()
      --i;                                            // c) make it zero based
      if (i >= 0) name = m_slots[i];                  // d) get the name
   }

   return name;
}

//------------------------------------------------------------------------------
// index() -- returns the index of the slot named 'slotname'
//------------------------------------------------------------------------------
int SlotTable::index(const std::string& slotname) const
{
   int i {0};

   // First, check our slot names
   {
      // search our table
      int j {0};
      for (j = 0; j < m_slots.size(); j++) {
         if (slotname == m_slots[j]) break;
      }
      if (j < m_slots.size()) {
         // if we're here, we found a match
         i = j;                                    // a) start with j
         i++;                                      // b) make it one based
         if (baseTable != nullptr) i += baseTable->n();  // c) add baseTable->n()
      }
   }

   // Second, check our baseTable
   if (i == 0 && baseTable != nullptr) i = baseTable->index(slotname);

   return i;
}

}
}

