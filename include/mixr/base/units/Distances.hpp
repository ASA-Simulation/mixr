
#ifndef __mixr_base_Distance_H__
#define __mixr_base_Distance_H__

#include "mixr/base/numeric/Number.hpp"
#include "mixr/base/units/distance_utils.hpp"
#include <iostream>

namespace mixr {
namespace base {

//------------------------------------------------------------------------------
// Class: Distance
// Description:  Base class for distances.  Defined as a meter which is
//               equivalent to an instance of Meters with its value equal
//               to 1.0.
//
//
// Public methods (Defined in Distance, and inherited by all derived classes):
//
//     set(const double v)
//        Sets a Distance derived instance with an double.
//
//     set(const Distance& n)
//        Sets, and converts if necessary, a Distance derived instance with
//        another Distance derived instance.
//
//     double convert(const Distance& n)
//        Converts the value of a Distance derived instance into
//        the units of another Distance derived instance.
//
//
// Output stream operator:  >>
//       ostream& operator<<(ostream& sout, const Distance& n)
//          Sends "( <the Distance derived instance class name and value> )"
//          to the output stream.
//
//
// Public methods (For classes:  Meters, CentiMeters, KiloMeters,
//                               Inches, Feet, NauticalMiles,
//                               StatuteMiles):
//
// double convertStatic(const Distance& n) const
//       Static function to convert the given Distance derived
//       instance into the units of a specific Distance derived
//       class.
//
//------------------------------------------------------------------------------
class Distance : public Number
{
    DECLARE_SUBCLASS(Distance, Number)

public:
    Distance();
    Distance(const double value);

    void set(const double v)                      { val = v; }
    void set(const Distance& n)                   { val = fromDistance(n.toDistance()); }

    virtual double toDistance() const = 0;
    virtual double fromDistance(const double) const = 0;
    double convert(const Distance& n)             { return fromDistance(n.toDistance()); }
};


inline std::ostream& operator<<(std::ostream& sout, const Distance& n)
{
   sout << "( " << n.getFactoryName() << " " << n.getReal() << " )";
   return sout;
}

//------------------------------------------------------------------------------
// Class: Meters
// Base class:  Object -> Number -> Distance -> Meters
// Description:  An instance of Meters with its value equal to 1.0 is one
//               base unit for distances.
//------------------------------------------------------------------------------
class Meters : public Distance
{
    DECLARE_SUBCLASS(Meters, Distance)

public:
    Meters();
    Meters(const double value);
    Meters(const Distance& value);

    static double convertStatic(const Distance& n)                { return n.toDistance(); }
    double toDistance() const override                            { return static_cast<double>(val); }
    double fromDistance(const double a) const override            { return a; }
};


//------------------------------------------------------------------------------
// Class:  CentiMeters
// Base class:  Object -> Number -> Distance -> CentiMeters
// Description:  Meters * 100.0
//------------------------------------------------------------------------------
class CentiMeters : public Distance
{
    DECLARE_SUBCLASS(CentiMeters, Distance)

public:
    CentiMeters();
    CentiMeters(const double value);
    CentiMeters(const Distance& value);

    static double convertStatic(const Distance& n)        { return n.toDistance() * distance::M2CM; }
    double toDistance() const override                    { return static_cast<double>(val * distance::CM2M); }
    double fromDistance(const double a) const override    { return a * distance::M2CM; }
};



//------------------------------------------------------------------------------
// Class:  MicroMeters
// Base class:  Object -> Number -> Distance -> MicroMeters
// Description:  Meters * 1,000,000.0
//------------------------------------------------------------------------------
class MicroMeters : public Distance
{
    DECLARE_SUBCLASS(MicroMeters, Distance)

public:
    MicroMeters();
    MicroMeters(const double value);
    MicroMeters(const Distance& value);

    static double convertStatic(const Distance& n)       { return n.toDistance() * distance::M2UM; }
    double toDistance() const override                   { return static_cast<double>(val * distance::UM2M); }
    double fromDistance(const double a) const override   { return a * distance::M2UM; }
};

//------------------------------------------------------------------------------
// Class: Microns(Same as MicroMeters)
// Base class:  Object -> Number -> Distance -> MicroMeters
// Description:  Meters * 1,000,000.0
//------------------------------------------------------------------------------
class Microns : public Distance
{
    DECLARE_SUBCLASS(Microns, Distance)

public:
    Microns();
    Microns(const double value);
    Microns(const Distance& value);

    static double convertStatic(const Distance& n)       { return n.toDistance() * distance::M2UM; }
    double toDistance() const override                   { return static_cast<double>(val * distance::UM2M); }
    double fromDistance(const double a) const override   { return a * distance::M2UM; }
};
//------------------------------------------------------------------------------
// Class:  KiloMeters
// Base class:  Object -> Number -> Distance -> KiloMeters
// Description:  Meters / 1000.0
//------------------------------------------------------------------------------
class KiloMeters : public Distance
{
    DECLARE_SUBCLASS(KiloMeters, Distance)

public:
    KiloMeters();
    KiloMeters(const double value);
    KiloMeters(const Distance& value);

    static double convertStatic(const Distance& n)      { return n.toDistance() * distance::M2KM; }
    double toDistance() const override                  { return static_cast<double>(val * distance::KM2M); }
    double fromDistance(const double a) const override  { return a * distance::M2KM; }
};


//------------------------------------------------------------------------------
// Class:  Inches
// Base class:  Object -> Number -> Distance -> Inches
// Description:  Meters / 0.0254
//------------------------------------------------------------------------------
class Inches : public Distance
{
    DECLARE_SUBCLASS(Inches, Distance)

public:
    Inches();
    Inches(const double value);
    Inches(const Distance& value);

    static double convertStatic(const Distance& n)      { return n.toDistance() * distance::M2IN; }
    double toDistance() const override                  { return static_cast<double>(val * distance::IN2M); }
    double fromDistance(const double a) const override  { return a * distance::M2IN; }
};


//------------------------------------------------------------------------------
// Class:  Feet
// Base class:  Object -> Number -> Distance -> Feet
// Description:  Meters / 0.3048
//------------------------------------------------------------------------------
class Feet : public Distance
{
    DECLARE_SUBCLASS(Feet, Distance)

public:
    Feet();
    Feet(const double value);
    Feet(const Distance& value);

    static double convertStatic(const Distance& n)      { return n.toDistance() * distance::M2FT; }
    double toDistance() const override                  { return static_cast<double>(val * distance::FT2M); }
    double fromDistance(const double a) const override  { return a * distance::M2FT; }
};


//------------------------------------------------------------------------------
// Class:  NauticalMiles
// Base class:  Object -> Number -> Distance -> NauticalMiles
// Description:  Meters * 1851.999942
//------------------------------------------------------------------------------
class NauticalMiles : public Distance
{
    DECLARE_SUBCLASS(NauticalMiles, Distance)

public:
    NauticalMiles();
    NauticalMiles(const double value);
    NauticalMiles(const Distance& value);

    static double convertStatic(const Distance& n)     { return n.toDistance() * distance::M2NM; }
    double toDistance() const override                 { return static_cast<double>(val * distance::NM2M); }
    double fromDistance(const double a) const override { return a * distance::M2NM; }
};


//------------------------------------------------------------------------------
// Class:  StatuteMiles
// Base class:  Object -> Number -> Distance -> StatuteMiles
// Description:  Meters * 1609.34313095
//------------------------------------------------------------------------------
class StatuteMiles : public Distance
{
    DECLARE_SUBCLASS(StatuteMiles, Distance)

public:
    StatuteMiles();
    StatuteMiles(const double value);
    StatuteMiles(const Distance& value);

    static double convertStatic(const Distance& n)      { return n.toDistance() * distance::M2SM; }
    double toDistance() const override                  { return static_cast<double>(val * distance::SM2M); }
    double fromDistance(const double a) const override  { return a * distance::M2SM; }
};

}
}

#endif
