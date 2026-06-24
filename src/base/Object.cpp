
#include "mixr/base/Object.hpp"

#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

namespace mixr {
namespace base {

// ---
// Class and object metadata
// ---
const std::shared_ptr<const MetaObject> Object::metaObject = \
   std::make_shared<const MetaObject>(
      typeid(Object).name(),
      "Object",
      nullptr
   );

// ---
// Object's SlotTable
//    Note: Keep our slot table empty.  There are several light weight classes derived
//    from Object (e.g., the classes for colors, numbers and units) that expect their
//    slots to be the first slots -- starting at slot number 1.
// ---
// const std::string Object::slotnames[] = { "" };
// const int Object::nslots {};
const std::shared_ptr<const SlotTable> Object::slotTable = \
   std::make_shared<const SlotTable>(
      std::vector<std::string>(),
      nullptr
   );

//------------------------------------------------------------------------------
// Standard object stuff -- derived classes used macro IMPLEMENT_SUBCLASS, see macros.hpp
//------------------------------------------------------------------------------

// Object& Object::operator=(const Object& org)
// {
//    Object tmp(org);
//    std::swap(*this, tmp);
//    return *this;
// }

std::shared_ptr<Object> Object::clone() const
{
   return std::make_shared<Object>(*this);
}

// Check class type
bool Object::isClassType(const std::type_info& type) const
{
    if ( type == typeid(Object) ) return true;
    else return false;
}

// Check factory name
bool Object::isFactoryName(const std::string& name) const
{
    if (name.empty()) return false;
    if ( metaObject->getFactoryName() == name )  return true;
    else return false;
}

// set slots by index
bool Object::setSlotByIndex(const int, Element)
{
    // We have no slots, so we shouldn't ever be here!
    return false;
}

// set slot by index
Element Object::getSlotByIndex(const int slotindex) const
{
   return nullptr;
}

const std::string& Object::getFactoryName()
{
    return Object::metaObject->getFactoryName();
}

const std::shared_ptr<const SlotTable>& Object::getSlotTable() const
{
   return Object::slotTable;
}

//------------------------------------------------------------------------------
// slotName2Index() -- returns the index of the slot named 'slotname'
//------------------------------------------------------------------------------
int Object::slotName2Index(const std::string& slotname) const
{
   int slotindex {};

   // No 'slotname' then no slot index
   if (slotname == "") {
      return slotindex;
   }

   // How many slots do we have
   int n {getSlotTable()->n()};

   // a) check if 'slotname' is a number (e.g., "12")
   bool isNum {true};
   for (int i = 0; isNum && slotname[i] != '\0'; i++) {
      if ( !std::isdigit(slotname[i]) ) {
         isNum = false;
      }
   }

   // b) convert 'slotname' to a slot index
   if (isNum) {
      // when the slotname is just a number (e.g., "12")
      int j {std::stoi(slotname)};
      if (j > 0 && j <= n) {
         slotindex = j;
      }
   } else {
      // when the 'slotname' is a name (e.g., "some-slot")
      slotindex = getSlotTable()->index(slotname.data());
      if (slotindex <= 0)
         std::cerr << "slot not found: " << slotname << std::endl;
   }
   return slotindex;
}

//------------------------------------------------------------------------------
// setSlotByName() -- set the value of slot 'slotname' to 'obj'  Returns
//                 true if the slot and object were processed; returns
//                 false if there was an error.
//------------------------------------------------------------------------------
bool Object::setSlotByName(std::string slotname, Element obj)
{
    bool ok {false};
    const int slotindex {slotName2Index(slotname)};
    if (slotindex > 0) {
        ok = setSlotByIndex(slotindex,{obj});
    }
    return ok;
}

//------------------------------------------------------------------------------
// getSlotByName() -- get the value of slot 'slotname'.
//------------------------------------------------------------------------------
Element Object::getSlotByName(std::string slotname) const
{
    const int slotindex {slotName2Index(slotname)};
    if (slotindex > 0) {
        return getSlotByIndex(slotindex);
    }
    return nullptr;
}

//------------------------------------------------------------------------------
// slotIndex2Name() -- returns the name of the slot at 'slotindex'
//------------------------------------------------------------------------------
const std::string Object::slotIndex2Name(const int slotindex) const
{
   return getSlotTable()->name(slotindex).value_or("");
}

//------------------------------------------------------------------------------
// isValid() -- is this a valid object
//------------------------------------------------------------------------------
bool Object::isValid() const
{
   return true;
}

//------------------------------------------------------------------------------
// Message types
//------------------------------------------------------------------------------

bool Object::isMessageEnabled(const unsigned short msgType) const
{
   bool enabled {};

   if (msgType != 0) {
      if ((msgType & MSG_ERROR) != 0) {
         // Error messages are always enabled
         enabled = true;
      } else {
         // enabled if any bits match
         enabled = (msgType & enbMsgBits) != 0;
      }
   }
   return enabled;
}

bool Object::isMessageDisabled(const unsigned short msgType) const
{
   bool disabled {};

   if (msgType != 0) {
      if ((msgType & MSG_ERROR) != 0) {
         // Error messages are not disabled
         disabled = false;
      } else {
         // disabled if any bits match
         disabled = (msgType & disMsgBits) != 0;
      }
   }

   return disabled;
}

bool Object::enableMessageTypes(const unsigned short msgTypeBits)
{
   // Set the enabled bits
   enbMsgBits |= msgTypeBits;

   // Clear the disabled bits
   disMsgBits &= ~msgTypeBits;

   return true;
}

bool Object::disableMessageTypes(const unsigned short msgTypeBits)
{
   // Set the disabled bits
   disMsgBits |= msgTypeBits;

   // Clear the enabled bits
   enbMsgBits &= ~msgTypeBits;

   return true;
}

//------------------------------------------------------------------------------
// return object and class metadata
//------------------------------------------------------------------------------
const std::shared_ptr<const MetaObject>& Object::getMetaObject() const
{
   return Object::metaObject;
}

}
}

