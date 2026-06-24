#pragma once

#include <string>
#include <memory>

namespace mixr {
namespace base {

class SlotTable;

//------------------------------------------------------------------------------
// Class: MetaObject
// Description: MetaObject about class attributes and object instances.  This includes its name,
//              slot table, and even the number of them in existence
//------------------------------------------------------------------------------
class MetaObject
{
public:
   MetaObject(const char* const, const std::string&, const std::shared_ptr<const MetaObject>&);
   MetaObject(const MetaObject&) = delete;
   MetaObject& operator=(const MetaObject&) = delete;

   const std::string& getClassName() const        { return m_class_name; }
   const std::string& getFactoryName() const      { return m_factory_name; }

   const std::shared_ptr<const MetaObject> baseMetaObject;   // pointer to the base object's MetaObject

private:
   const std::string m_class_name;                // class name from 'type_info'
   const std::string m_factory_name;              // factory name
};

}

}


