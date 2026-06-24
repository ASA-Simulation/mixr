#pragma once

#include "mixr/base/numeric/Number.hpp"
#include "mixr/base/units/Masses.hpp"
#include "mixr/base/units/Volumes.hpp"

namespace mixr {
namespace base {

//------------------------------------------------------------------------------
// Classes: Density
//
// Description:  Density as a function of mass and volume.
//
// Factory name: Density
// Slots:
//    mass    <Mass>    ! Mass (default: 1 kg)
//    volume  <Volume>  ! Volume (default: 1 m^3)
//
// getMassUnits() -- get units of this density object
//     const Mass* Density::getMass() const
//
// getVolumeUnits() -- get units of this density object
//     const Volume* Density::getVolume() const
//
// setSlotMass() -- sets our mass object.
//     bool Density::setSlotMass(std::shared_ptr<const Mass> newMass)
//
// setSlotVolume() -- sets our volume object.
//     bool Density::setSlotVolume(std::shared_ptr<const Volume> newVolume)
//
// set() -- sets our density from some other density
//     void Density::set(const Density& n)
//
// convert() -- converts from one mass/volume ratio to another
//     double Density::convert(const Density& n) const
//
// NOTE: The = operator and copy constructor WILL change the units
// of the target density object.  To perform a conversion, use set().
//------------------------------------------------------------------------------
class Density : public Number
{
    DECLARE_SUBCLASS(Density, Number)

public:
    Density(double newDensity, std::shared_ptr<const Mass> newMass, std::shared_ptr<const Volume> newVolume);
    Density();

    double convert(const Density& n) const;
    void set(const Density& n);
    std::shared_ptr<const Mass> getMass() const;
    std::shared_ptr<const Volume> getVolume() const;

private:
    std::shared_ptr<const Mass>   myMass;
    std::shared_ptr<const Volume> myVolume;

private:
    // slot table helper methods
    bool setSlotMass(std::shared_ptr<const Mass>);
    bool setSlotVolume(std::shared_ptr<const Volume>);
};

inline std::ostream& operator<<(std::ostream& sout, const Density& n)
{
    std::shared_ptr<const Mass> m {n.getMass()};
    std::shared_ptr<const Volume> v {n.getVolume()};

    sout << "( " << n.getFactoryName() << " " << n.getReal();
    if ( m != nullptr ) sout << " " << *m;
    if ( v != nullptr ) sout << " " << *v;
    sout << " )";
    return sout;
}

}
}
