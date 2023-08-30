
#include "mixr/models/TargetData.hpp"

#include "mixr/base/numeric/Number.hpp"

#include "mixr/base/Identifier.hpp"
#include "mixr/base/String.hpp"

#include "mixr/base/units/Angles.hpp"
#include "mixr/base/units/Distances.hpp"
#include "mixr/base/units/Times.hpp"

namespace mixr {
namespace models {

IMPLEMENT_SUBCLASS(TargetData, "TargetData")

BEGIN_SLOTTABLE(TargetData)
   "enabled",             //  1) Target enabled flag (default: false)
   "completed",           //  2) Target completed flag (default: false)
   "weaponType",          //  3) Type of weapon to release (default: 0)
   "quantity",            //  4) Number of weapons to release (default: 0)
   "manualAssign",        //  5) Manually assign weapon to target? (default: false)
   "stickType",           //  6) Weapon stick option (MIDPOINT, LEADING_EDGE) (default: MIDPOINT)
   "stickDistance",       //  7) Weapon stick length (default: 0
   "interval",            //  8) Time between weapon releases (default: 0)
   "maxMissDistance",     //  9) Maximum miss distance (default: 0)
   "armDelay",            // 10) Arming delay (default: 0)
   "angle",               // 11) Impact angle (default: 0)
   "azimuth",             // 12) Azimuth angle (default: 0)
   "velocity",            // 13) Impact velocity (ft/sec) (default: 0)
END_SLOTTABLE(TargetData)

BEGIN_SLOT_MAP(TargetData)
   ON_SLOT( 1, setSlotEnabled,         base::Number)
   ON_SLOT( 2, setSlotCompleted,       base::Number)
   ON_SLOT( 3, setSlotWpnType,         base::String)
   ON_SLOT( 4, setSlotQuantity,        base::Number)
   ON_SLOT( 5, setSlotManualAssign,    base::Number)
   ON_SLOT( 6, setSlotStickType,       base::Identifier)

   ON_SLOT( 7, setSlotStickDistance,   base::Distance)
   ON_SLOT( 7, setSlotStickDistance,   base::Number)

   ON_SLOT( 8, setSlotInterval,        base::Time)
   ON_SLOT( 8, setSlotInterval,        base::Number)

   ON_SLOT( 9, setSlotMaxMissDistance, base::Distance)
   ON_SLOT( 9, setSlotMaxMissDistance, base::Number)

   ON_SLOT(10, setSlotArmDelay,        base::Time)
   ON_SLOT(10, setSlotArmDelay,        base::Number)

   ON_SLOT(11, setSlotAngle,           base::Angle)
   ON_SLOT(11, setSlotAngle,           base::Number)

   ON_SLOT(12, setSlotAzimuth,         base::Angle)
   ON_SLOT(12, setSlotAzimuth,         base::Number)
   ON_SLOT(13, setSlotVelocity,        base::Number)
END_SLOT_MAP()

TargetData::TargetData()
{
   STANDARD_CONSTRUCTOR()
}

void TargetData::copyData(const TargetData& org, const bool)
{
   BaseClass::copyData(org);

   enabled      = org.enabled;
   completed    = org.completed;
   setWpnType(org.wpnType);
   quantity     = org.quantity;
   stickType    = org.stickType;
   stickDist    = org.stickDist;
   maxMissDist  = org.maxMissDist;
   interval     = org.interval;
   manualAssign = org.manualAssign;
   armDelay     = org.armDelay;
   angle        = org.angle;
   azimuth      = org.azimuth;
   velocity     = org.velocity;
}

void TargetData::deleteData()
{
   setWpnType(nullptr);
}

//------------------------------------------------------------------------------
// Set functions
//------------------------------------------------------------------------------
bool TargetData::setEnabled(const bool b)             { enabled = b; return true; }
bool TargetData::setCompleted(const bool b)           { completed = b; return true; }
bool TargetData::setQuantity(const unsigned int q)    { quantity = q; return true; }
bool TargetData::setStickType(const unsigned int t)   { stickType = t; return true; }
bool TargetData::setStickDistance(const double ft)    { stickDist = ft; return true; }
bool TargetData::setMaxMissDistance(const double ft)  { maxMissDist = ft; return true; }
bool TargetData::setInterval(const double ms)         { interval = ms; return true; }
bool TargetData::setManualAssign(const bool b)        { manualAssign = b; return true; }
bool TargetData::setArmDelay(const double sec)        { armDelay = sec; return true; }
bool TargetData::setAngle(const double degs)          { angle = degs; return true; }
bool TargetData::setAzimuth(const double degs)        { azimuth = degs; return true; }
bool TargetData::setVelocity(const double fps)        { velocity = fps; return true; }

bool TargetData::setWpnType(const base::String* const s)
{
   if (wpnType != nullptr)
      wpnType->unref();

   wpnType = s;

   if (wpnType != nullptr)
      wpnType->ref();
   return true;
}


//------------------------------------------------------------------------------
// Set slot functions
//------------------------------------------------------------------------------
bool TargetData::setSlotEnabled(const base::Number* const msg)
{
   bool ok{};
   if (msg != nullptr) {
      ok = setEnabled(msg->getBoolean());
   }
   return ok;
}


bool TargetData::setSlotCompleted(const base::Number* const msg)
{
   bool ok{};
   if (msg != nullptr) {
      ok = setCompleted(msg->getBoolean());
   }
   return ok;
}


bool TargetData::setSlotWpnType(const base::String* const msg)
{
   return setWpnType(msg);
}

bool TargetData::setSlotQuantity(const base::Number* const msg)
{
   bool ok{};
   if (msg != nullptr) {
      const int v{msg->getInt()};
      if (v >= 0) {
         ok = setQuantity(static_cast<unsigned int>(msg->getInt()));
      }
   }
   return ok;
}

bool TargetData::setSlotManualAssign(const base::Number* const msg)
{
   bool ok{};
   if (msg != nullptr) {
      ok = setManualAssign(msg->getBoolean());
   }
   return ok;
}

bool TargetData::setSlotStickType(const base::Identifier* const msg)
{
   bool ok{};
   if (msg != nullptr) {
      if (*msg == "MIDPOINT" || *msg == "midpoint") {
         ok = setStickType(MIDPOINT);
      } else if (*msg == "LEADING_EDGE" || *msg == "leading_edge") {
         ok = setStickType(LEADING_EDGE);
      } else {
         std::cerr << "TargetData::setSlotStickType(): invalid type: " << *msg << std::endl;
         std::cerr << " -- valid types are { MIDPOINT, LEADING_EDGE }" << std::endl;
      }
   }
   return ok;
}

bool TargetData::setSlotStickDistance(const base::Distance* const msg)
{
   bool ok{};
   if (msg != nullptr) {
      ok = setStickDistance( base::Feet::convertStatic(*msg) );
   }
   return ok;
}

bool TargetData::setSlotStickDistance(const base::Number* const msg)
{
   bool ok{};
   if (msg != nullptr) {
      ok = setStickDistance(msg->getDouble());
   }
   return ok;
}

bool TargetData::setSlotInterval(const base::Time* const msg)
{
   bool ok{};
   if (msg != nullptr) {
      ok = setInterval( base::MilliSeconds::convertStatic(*msg) );
   }
   return ok;
}

bool TargetData::setSlotInterval(const base::Number* const msg)
{
   bool ok{};
   if (msg != nullptr) {
      ok = setInterval(msg->getDouble());
   }
   return ok;
}

bool TargetData::setSlotMaxMissDistance(const base::Distance* const msg)
{
   bool ok{};
   if (msg != nullptr) {
      ok = setMaxMissDistance( base::Feet::convertStatic(*msg) );
   }
   return ok;
}

bool TargetData::setSlotMaxMissDistance(const base::Number* const msg)
{
   bool ok{};
   if (msg != nullptr) {
      ok = setMaxMissDistance(msg->getDouble());
   }
   return ok;
}

bool TargetData::setSlotArmDelay(const base::Time* const msg)
{
   bool ok{};
   if (msg != nullptr) {
      ok = setArmDelay( base::Seconds::convertStatic(*msg) );
   }
   return ok;
}

bool TargetData::setSlotArmDelay(const base::Number* const msg)
{
   bool ok{};
   if (msg != nullptr) {
      ok = setArmDelay(msg->getDouble());
   }
   return ok;
}

bool TargetData::setSlotAngle(const base::Angle* const msg)
{
   bool ok{};
   if (msg != nullptr) {
      ok = setAngle( base::Degrees::convertStatic(*msg) );
   }
   return ok;
}

bool TargetData::setSlotAngle(const base::Number* const msg)
{
   bool ok{};
   if (msg != nullptr) {
      ok = setAngle(msg->getDouble());
   }
   return ok;
}

bool TargetData::setSlotAzimuth(const base::Angle* const msg)
{
   bool ok{};
   if (msg != nullptr) {
      ok = setAzimuth( base::Degrees::convertStatic(*msg) );
   }
   return ok;
}

bool TargetData::setSlotAzimuth(const base::Number* const msg)
{
   bool ok{};
   if (msg != nullptr) {
      ok = setAzimuth(msg->getDouble());
   }
   return ok;
}

bool TargetData::setSlotVelocity(const base::Number* const msg)
{
   bool ok{};
   if (msg != nullptr) {
      ok = setVelocity(msg->getDouble());
   }
   return ok;
}

}
}
