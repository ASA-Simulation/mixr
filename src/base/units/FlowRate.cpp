
#include "mixr/base/units/FlowRate.hpp"
#include "mixr/base/SlotTable.hpp"

namespace mixr {
namespace base {

IMPLEMENT_SUBCLASS(FlowRate, "FlowRate")

BEGIN_SLOTTABLE(FlowRate)
    "volume",   // 1: Volume
    "flowTime", // 2: Time
END_SLOTTABLE(FlowRate)

BEGIN_SLOT_MAP(FlowRate)
    ON_SLOT(1, setSlotVolume, Volume)
    ON_SLOT(2, setSlotTime,   Time)
END_SLOT_MAP()

FlowRate::FlowRate(double newFlowRate, Volume* volume, Time* time)
{
    STANDARD_CONSTRUCTOR()

    // set our initial distance and time (default to meters per second)
    if (volume != nullptr && time != nullptr) {
        // find out what volume and time we are using, and reference them
        volume->ref();
        myVolume = volume;
        time->ref();
        myTime = time;
        flowRate = newFlowRate;

        // We are only using volume and time for units, not actual values, so they will default to 1 for conversion purposes
        myVolume->set(1);
        myTime->set(1);
    }
    else {
        if (isMessageEnabled(MSG_INFO)) {
            std::cout << "FlowRate::FlowRate() - missing a time or volume object, flow rate is default to 1.0 Cubic Feet per Second" << std::endl;
        }
        myVolume = new CubicFeet(1);
        myTime = new Seconds(1);
        flowRate = 1;
    }
}

FlowRate::FlowRate()
{
    STANDARD_CONSTRUCTOR()
    // default time, distance and flowRate
    myVolume = new CubicFeet(1);
    myTime = new Seconds(1);
    flowRate = 1;
}

void FlowRate::copyData(const FlowRate& org, const bool cc)
{
    BaseClass::copyData(org);
    if (cc) {
       myVolume = new CubicFeet(1);
       myTime = new Seconds(1);
    }

    if (myVolume != nullptr) myVolume = org.myVolume;
    if (myTime != nullptr) myTime = org.myTime;
    flowRate = org.flowRate;
}

void FlowRate::deleteData()
{
    if (myVolume != nullptr) myVolume->unref();
    myVolume = nullptr;

    if (myTime != nullptr) myTime->unref();
    myTime = nullptr;
}

//------------------------------------------------------------------------------
// convert() -- converts from one volume/time ratio to another
//------------------------------------------------------------------------------
double FlowRate::convert(Volume* newVolume, Time* newTime)
{
    // holds our converted flowRate
    double tempFR {1.0};
    // make sure we have a distance and a time to convert to
    if (newVolume != nullptr && newTime != nullptr) {
        double newVolVal {1.0};
        double newTimeVal {1.0};
        // Again, we are only concerned about the type of Volume and Time we have, not the actual value
        newVolume->set(1);
        newTime->set(1);
        // if we are different distances or times, we convert ourself to the new value, else
        // we will set our newVolVal and TimeVal to 1, to create the same flowRate.
        if (newVolume->getFactoryName() != myVolume->getFactoryName()) newVolVal = newVolume->convert(*myVolume);
        if (newTime->getFactoryName() != myTime->getFactoryName()) newTimeVal = newTime->convert(*myTime);

        // now we figure our new flowRate
        // Get our distance units first, then multiplies by a time factor
        tempFR = flowRate * newVolVal;
        tempFR *= newTimeVal;
    }
    else std::cerr << "FlowRate::convert() - missing a time or volume object!" << std::endl;

    return tempFR;
}

//------------------------------------------------------------------------------
// set() -- sets our velocity from some other velocity
//------------------------------------------------------------------------------
bool FlowRate::set(const double newFlowRate, Volume* newVolume, Time* newTime)
{
    bool ok {};
    // make sure we have a distance and a time to convert to
    if (newVolume != nullptr && newTime != nullptr) {
        double newVolVal {1.0};
        double newTimeVal {1.0};
        // we also have to set our units to 1 here, for conversion purposes
        newVolume->set(1);
        newTime->set(1);

        // if we are different distances or times, we convert ourself to the new value
        if (newVolume->getFactoryName() != myVolume->getFactoryName()) newVolVal = myVolume->convert(*newVolume);
        if (newTime->getFactoryName() != myTime->getFactoryName()) newTimeVal = myTime->convert(*newTime);

        // find our new velocity from the new velocity value we are given * the conversion constants
        double tempFR {newFlowRate * newVolVal};
        tempFR *= newTimeVal;

        ok = true;

        // set our new velocity value
        flowRate = tempFR;
    }
    else std::cerr << "FlowRate::set() - missing a time or distance object!" << std::endl;

    return ok;
}

bool FlowRate::setSlotVolume(Volume* newVol)
{
    bool ok {};
    if (newVol != nullptr) {
        newVol->set(1);
        myVolume = newVol;
        ok = true;
    }

    return ok;
}

bool FlowRate::setSlotTime(Time* newTime)
{
    bool ok {};
    if (newTime != nullptr) {
        newTime->set(1);
        myTime = newTime;
        ok = true;
    }

    return ok;
}

}
}
