
#include "mixr/models/Signatures.hpp"

#include "mixr/models/player/Player.hpp"

#include "mixr/models/Emission.hpp"

#include "mixr/base/Pair.hpp"
#include "mixr/base/PairStream.hpp"
#include "mixr/base/functors/Table2.hpp"

#include "mixr/base/units/Areas.hpp"
#include "mixr/base/units/Decibel.hpp"
#include "mixr/base/units/Distances.hpp"

#include <cmath>

namespace mixr {
namespace models {

//==============================================================================
// Class: RfSignature
//==============================================================================
IMPLEMENT_ABSTRACT_SUBCLASS(RfSignature, "Signature")
EMPTY_SLOTTABLE(RfSignature)
EMPTY_DELETEDATA(RfSignature)

RfSignature::RfSignature()
{
    STANDARD_CONSTRUCTOR()
}

void RfSignature::copyData(const RfSignature& org, const bool)
{
    BaseClass::copyData(org);
}


//==============================================================================
// Class: SigConstant
//==============================================================================
IMPLEMENT_SUBCLASS(SigConstant,"SigConstant")
EMPTY_DELETEDATA(SigConstant)

BEGIN_SLOTTABLE(SigConstant)
    "rcs",          // 1 Constant Radar Cross Section value
                    //   base::Number(square meters) or base::Decibel(square meters) or base::Area()
END_SLOTTABLE(SigConstant)

BEGIN_SLOT_MAP(SigConstant)
    ON_SLOT(1, setSlotRCS, base::Number)
END_SLOT_MAP()

SigConstant::SigConstant()
{
    STANDARD_CONSTRUCTOR()
}

SigConstant::SigConstant(const double r)
{
    STANDARD_CONSTRUCTOR()
    rcs = r;
}

SigConstant::SigConstant(const base::Number* const c)
{
    STANDARD_CONSTRUCTOR()
    setRCS(c);
}

void SigConstant::copyData(const SigConstant& org, const bool)
{
    BaseClass::copyData(org);
    rcs = org.rcs;
}

double SigConstant::getRCS(const Emission* const)
{
    return rcs;
}

bool SigConstant::setRCS(const base::Number* const num)
{
    bool ok{};
    double r{-1.0};

    const auto d = dynamic_cast<const base::Area*>(num);
    if (d != nullptr) {
        // Has area units and we need square meters
        base::SquareMeters m2;
        r = m2.convert(*d);
    } else if (num != nullptr) {
        // square meters (Number or Decibel)
        r = num->getReal();
    }

    if (r >= 0.0) { rcs = r; ok = true; }
    else { std::cerr << "SigConstant::setRCS: invalid rcs; must be greater than or equal to zero!" << std::endl; }
    return ok;
}

//==============================================================================
// Class: SigSphere
//==============================================================================
IMPLEMENT_SUBCLASS(SigSphere,"SigSphere")
EMPTY_DELETEDATA(SigSphere)

BEGIN_SLOTTABLE(SigSphere)
    "radius",       // 1 Radius of the sphere
END_SLOTTABLE(SigSphere)

BEGIN_SLOT_MAP(SigSphere)
    ON_SLOT(1, setSlotRadius, base::Number)
END_SLOT_MAP()

SigSphere::SigSphere()
{
    STANDARD_CONSTRUCTOR()
    setRadius(0);
}

SigSphere::SigSphere(const double r)
{
    STANDARD_CONSTRUCTOR()
    setRadius(r);
}

void SigSphere::copyData(const SigSphere& org, const bool)
{
    BaseClass::copyData(org);
    setRadius(org.radius);
}

//------------------------------------------------------------------------------
// getRCS() -- Get the RCS
//------------------------------------------------------------------------------
double SigSphere::getRCS(const Emission* const)
{
    return rcs;
}

//------------------------------------------------------------------------------
// setRadiusFromSlot() -- Set the radius from Slot table
//------------------------------------------------------------------------------
bool SigSphere::setSlotRadius(base::Number* const num)
{
    bool ok{};
    double r{-1.0};

    const auto d = dynamic_cast<base::Distance*>(num);
    if (d != nullptr) {
        // Has distance units and we need meters
        base::Meters meters;
        r = meters.convert(*d);
    } else if (num != nullptr) {
        // Just a Number
        r = num->getReal();
    }

    if (r >= 0.0) { setRadius(r); ok = true; }
    else { std::cerr << "SigSphere::setRadius: invalid radius; must be greater than or equal to zero!" << std::endl; }
    return ok;
}

//==============================================================================
// Class: SigPlate
//==============================================================================
IMPLEMENT_SUBCLASS(SigPlate,"SigPlate")

BEGIN_SLOTTABLE(SigPlate)
    "a",        // 1 length of the plate
    "b",        // 2 width of the plate
END_SLOTTABLE(SigPlate)

BEGIN_SLOT_MAP(SigPlate)
    ON_SLOT(1,setA,base::Number)
    ON_SLOT(2,setB,base::Number)
END_SLOT_MAP()

SigPlate::SigPlate()
{
    STANDARD_CONSTRUCTOR()
}

SigPlate::SigPlate(const double a1, const double b1)
{
    STANDARD_CONSTRUCTOR()
    a = a1;
    b = b1;
}

void SigPlate::copyData(const SigPlate& org, const bool)
{
    BaseClass::copyData(org);
    a = org.a;
    b = org.b;
}

void SigPlate::deleteData()
{
}

//------------------------------------------------------------------------------
// getRCS() -- Get the RCS
//------------------------------------------------------------------------------
double SigPlate::getRCS(const Emission* const em)
{
    double rcs{};
    if (em != nullptr) {
        double lambda{em->getWavelength()};
        double area{a * b};
        if (lambda > 0.0 && area > 0.0) {
            // If we have lambda and the area of the plate, compute the RCS
            rcs = (4.0 * base::PI * area * area) / (lambda * lambda);
        }
    }
    return static_cast<double>(rcs);
}

//------------------------------------------------------------------------------
// setA() -- Set the length
//------------------------------------------------------------------------------
bool SigPlate::setA(base::Number* const num)
{
    bool ok{};
    double v{-1.0};

    const auto d = dynamic_cast<base::Distance*>(num);
    if (d != nullptr) {
        // Has distance units and we need meters
        base::Meters meters;
        v = meters.convert(*d);
    } else if (num != nullptr) {
        // Just a Number
        v = num->getReal();
    }

    if (v >= 0.0) { a = v; ok = true; }
    else { std::cerr << "SigPlate::setWidthFromSlot: invalid: must be greater than or equal to zero!" << std::endl; }
    return ok;
}

//------------------------------------------------------------------------------
// setB() -- Set the width
//------------------------------------------------------------------------------
bool SigPlate::setB(base::Number* const num)
{
    bool ok{};
    double v{-1.0};

    const auto d = dynamic_cast<base::Distance*>(num);
    if (d != nullptr) {
        // Has distance units and we need meters
        base::Meters meters;
        v = meters.convert(*d);
    } else if (num != nullptr) {
        // Just a Number
        v = num->getReal();
    }

    if (v >= 0.0) { b = v; ok = true; }
    else { std::cerr << "SigPlate::setHeightFromSlot: invalid: must be greater than or equal to zero!" << std::endl; }
    return ok;
}

//==============================================================================
// Class: SigDihedralCR
//==============================================================================
IMPLEMENT_SUBCLASS(SigDihedralCR, "SigDihedralCR")
EMPTY_SLOTTABLE(SigDihedralCR)

SigDihedralCR::SigDihedralCR()
{
    STANDARD_CONSTRUCTOR()
    length = 0.0;
}

SigDihedralCR::SigDihedralCR(const double a) : SigPlate(a, 0.0)
{
    STANDARD_CONSTRUCTOR()
    length = 0.0;
}

void SigDihedralCR::copyData(const SigDihedralCR& org, const bool)
{
    BaseClass::copyData(org);
}

void SigDihedralCR::deleteData()
{
}

//------------------------------------------------------------------------------
// getRCS() -- Get the RCS
//------------------------------------------------------------------------------
double SigDihedralCR::getRCS(const Emission* const em)
{
    double rcs{};
    if (em != nullptr) {
        const double lambda{em->getWavelength()};
        if (lambda > 0.0) {
            // If we have lambda and the area of the plate, compute the RCS
            const double a{getA()};
            rcs = (8.0 * base::PI * a*a*a*a) / (lambda*lambda);
        }
    }
    return static_cast<double>(rcs);
}


//==============================================================================
// Class: SigTrihedralCR
//==============================================================================
IMPLEMENT_SUBCLASS(SigTrihedralCR, "SigTrihedralCR")
EMPTY_SLOTTABLE(SigTrihedralCR)
EMPTY_DELETEDATA(SigTrihedralCR)
EMPTY_COPYDATA(SigTrihedralCR)

SigTrihedralCR::SigTrihedralCR()
{
    STANDARD_CONSTRUCTOR()
}

SigTrihedralCR::SigTrihedralCR(const double a) : SigDihedralCR(a)
{
    STANDARD_CONSTRUCTOR()
}

//------------------------------------------------------------------------------
// getRCS() -- Get the RCS
//------------------------------------------------------------------------------
double SigTrihedralCR::getRCS(const Emission* const em)
{
    double rcs{};
    if (em != nullptr) {
        const double lambda{em->getWavelength()};
        if (lambda > 0.0) {
            // If we have lambda and the area of the plate, compute the RCS
            const double a{getA()};
            rcs = (12.0 * base::PI * a*a*a*a) / (lambda*lambda);
        }
    }
    return static_cast<double>(rcs);
}

//==============================================================================
// Class: SigSwitch
//==============================================================================
IMPLEMENT_SUBCLASS(SigSwitch, "SigSwitch")
EMPTY_SLOTTABLE(SigSwitch)
EMPTY_DELETEDATA(SigSwitch)
EMPTY_COPYDATA(SigSwitch)

SigSwitch::SigSwitch()
{
   STANDARD_CONSTRUCTOR()
}

//------------------------------------------------------------------------------
// getRCS() -- Get the RCS
//------------------------------------------------------------------------------
double SigSwitch::getRCS(const Emission* const em)
{
   double rcs{};

   // Find our ownship player ...
   const Player* ownship{static_cast<const Player*>(findContainerByType(typeid(Player)))};
   if (ownship != nullptr) {

      // get our ownship's camouflage type
      unsigned int camouflage{ownship->getCamouflageType()};
      camouflage++; // our components are one based

      // find a RfSignature with this index
      base::Pair* pair{findByIndex(camouflage)};
      if (pair != nullptr) {
         const auto sig = dynamic_cast<RfSignature*>( pair->object() );
         if (sig != nullptr) {

            // OK -- we've found the correct RfSignature subcomponent
            // now let it do all of the work
            rcs = sig->getRCS(em);

         }
      }
   }
   return rcs;
}


//==============================================================================
// Class: SigAzEl
//==============================================================================
IMPLEMENT_SUBCLASS(SigAzEl, "SigAzEl")

BEGIN_SLOTTABLE(SigAzEl)
    "table",            // 1: Table of RCS by target Az/El angles  (base::Table2)
    "swapOrder",        // 2: True if elevation is the table's first independent
                        //    variable and azimuth is the second.
    "inDegrees",        // 3: True if the table's independent variables az and
                        //    el are in degrees instead of the default radians
    "inDecibel",        // 4: True if the dependent data is in decibel meters
                        //    squared instead of the default meters squared
END_SLOTTABLE(SigAzEl)

BEGIN_SLOT_MAP(SigAzEl)
    ON_SLOT(1, setSlotTable,        base::Table2)
    ON_SLOT(2, setSlotSwapOrder,    base::Number)
    ON_SLOT(3, setSlotInDegrees,    base::Number)
    ON_SLOT(4, setSlotDecibel,      base::Number)
END_SLOT_MAP()

SigAzEl::SigAzEl()
{
   STANDARD_CONSTRUCTOR()
}

SigAzEl::SigAzEl(const base::Table2* const tbl0)
{
   STANDARD_CONSTRUCTOR()

   if (tbl0 != nullptr) {
      tbl = tbl0->clone();
   }
}

void SigAzEl::copyData(const SigAzEl& org, const bool)
{
   BaseClass::copyData(org);

   if (tbl != nullptr) { tbl->unref(); tbl = nullptr; }
   if (org.tbl != nullptr) {
      tbl = org.tbl->clone();
   }

   swapOrderFlg = org.swapOrderFlg;
   degFlg = org.degFlg;
   dbFlg = org.dbFlg;
}

void SigAzEl::deleteData()
{
    if (tbl != nullptr) { tbl->unref(); tbl = nullptr; }
}

//------------------------------------------------------------------------------
// getRCS() -- Get the RCS
//------------------------------------------------------------------------------
double SigAzEl::getRCS(const Emission* const em)
{
   double rcs{};
   if (em != nullptr && tbl != nullptr) {

      // angle of arrival (radians)
      double iv1{em->getAzimuthAoi()};
      double iv2{em->getElevationAoi()};

      // If the table's independent variable's order is swapped: (El, Az)
      if (isOrderSwapped()) {
         iv1 = em->getElevationAoi();
         iv2 = em->getAzimuthAoi();
      }

      // If the table's independent variables are in degrees ..
      if (isInDegrees()) {
         iv1 *= static_cast<double>(base::angle::R2DCC);
         iv2 *= static_cast<double>(base::angle::R2DCC);
      }

      rcs = tbl->lfi(iv1,iv2);

      // If the dependent data is in decibels ...
      if (isDecibel()) {
         rcs = std::pow(static_cast<double>(10.0), static_cast<double>(rcs / 10.0));
      }
   }
   return rcs;
}

//------------------------------------------------------------------------------
// isTableValid() -- Returns true if this signature has a good az/el table
//------------------------------------------------------------------------------
bool SigAzEl::isTableValid() const
{
   bool ok{};
   if (tbl != nullptr) {
      ok = tbl->isValid();
   }
   return ok;
}

//------------------------------------------------------------------------------
// Set functions
//------------------------------------------------------------------------------

bool SigAzEl::setSwapOrder(const bool flg)
{
   swapOrderFlg = flg;
   return true;
}

bool SigAzEl::setInDegrees(const bool flg)
{
   degFlg = flg;
   return true;
}

bool SigAzEl::setDecibel(const bool flg)
{
   dbFlg = flg;
   return true;
}

//------------------------------------------------------------------------------
// Slot functions
//------------------------------------------------------------------------------

// Sets the signature table
bool SigAzEl::setSlotTable(const base::Table2* const msg)
{
   bool ok{};
   if (msg != nullptr) {
      if (tbl != nullptr) tbl->unref();
      msg->ref();
      tbl = msg;
      ok = true;
   }
   return ok;
}

bool SigAzEl::setSlotSwapOrder(const base::Number* const msg)
{
   bool ok{};
   if (msg != nullptr) {
      ok = setSwapOrder( msg->getBoolean() );
   }
   return ok;
}

bool SigAzEl::setSlotInDegrees(const base::Number* const msg)
{
   bool ok{};
   if (msg != nullptr) {
      ok = setInDegrees( msg->getBoolean() );
   }
   return ok;
}

bool SigAzEl::setSlotDecibel(const base::Number* const msg)
{
   bool ok{};
   if (msg != nullptr) {
      ok = setDecibel( msg->getBoolean() );
   }
   return ok;
}

}
}
