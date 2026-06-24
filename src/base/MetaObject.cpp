#include "mixr/base/MetaObject.hpp"

namespace mixr {
namespace base {

MetaObject::MetaObject(
      const char* const cname,
      const std::string& fname,
      const std::shared_ptr<const MetaObject>& metaobj
   ) : baseMetaObject(metaobj), m_class_name(cname), m_factory_name(fname)
{}

}
}

