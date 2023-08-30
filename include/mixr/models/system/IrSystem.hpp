
#ifndef __mixr_models_IrSystem_H__
#define __mixr_models_IrSystem_H__

#include "mixr/models/system/System.hpp"

namespace mixr {
namespace models {
class IrSeeker;
class IrQueryMsg;
class OnboardComputer;

//------------------------------------------------------------------------------
// Class: IrSystem
//
// Description: Generic class for IR type systems.  Provides a common
//              interface, and some default behavior, for IR systems.
//
// Notes
//    1) By convention, IR systems are responsible for filtering their own players
//    of interest, so there is the processPlayersOfInterest() function, which is
//    called by our updateData(), that can be used by our derived classes to filter
//    players, as needed.  The Gimbal class, which is used to create antennas and
//    seekers, has its own member function processPlayersOfInterest() that filters
//    by gimbal field of view and player type.  It's the responsibility of the
//    various IR systems to use or not use this gimbal function -- our default
//    member function processPlayersOfInterest() does use the gimbal function.
//
// Factory name: IrSystem
// Slots:
//    seekerName     <String>    Name of the requested Seeker (default: 0)
//    disableQueries <Boolean>   Disable sending queries packets flag (default: false)
//
//------------------------------------------------------------------------------
class IrSystem : public System
{
   DECLARE_SUBCLASS(IrSystem, System)

public:
   IrSystem();

   virtual bool isQuerying() const;

   virtual bool areQueriesDisabled() const;              // Returns true if sending query packets has been disabled
   virtual bool setDisableQueriesFlag(const bool b);     // Disables/enables sending the I/R queries packets

   virtual IrSeeker* getSeeker();                        // Get the seeker model, or zero (0) if none
   virtual const IrSeeker* getSeeker() const;            // Get the seeker model (const version)
   virtual bool setSeeker(IrSeeker* const p);            // Sets the IR's seeker model

   virtual const base::String* getSeekerName() const;   // Name of the seeker model, or zero (0) if none

   void updateData(const double dt = 0.0) override;
   void reset() override;

protected:

   // Process players of interest -- Called by our updateData() -- the background thread --
   // This function will create a filtered list of players that IR systems will interact with.
   virtual void processPlayersOfInterest();

   bool shutdownNotification() override;

private:
   IrSeeker* seeker {};            // Our seeker
   base::String* seekerName {};    // Name of our seeker

   bool disableQueries {};         // Disable sending queries flag

private:
   // slot table helper methods
   bool setSlotSeekerName(base::String* const);
   bool setSlotDisableQueries(base::Number* const);
};

}
}

#endif
