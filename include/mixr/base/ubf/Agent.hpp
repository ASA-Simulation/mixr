
#ifndef __mixr_base_ubf_Agent_H__
#define __mixr_base_ubf_Agent_H__

#include "mixr/base/Component.hpp"

namespace mixr {
namespace base {
namespace ubf {
class AbstractBehavior;
class AbstractState;
class AbstractAction;

//------------------------------------------------------------------------------
// Class: Agent
//
// Description: Generic agent class to control a component in the simulation - the agent's "actor"
//              It manages a component (the "actor") with a behavior (either a player, or
//              a player's component)
//
// Notes:
// 1) Use 'Agent' to update the behavior framework via updateData() and use
//    'AgentTC' to update the behavior framework using updateTC().
//
// 2) The updateData() and updateTC() calls are only processed by this Agent
//    class and are not passed to the rest of the behavior framework.
//
//
// Factory name: UbfAgent
// Slots:
//    state       <AbstractState>     ! The agent's state object
//    behavior    <AbstractBehavior>  ! behavior
//------------------------------------------------------------------------------
class Agent : public base::Component
{
   DECLARE_SUBCLASS(Agent, base::Component)

public:
   Agent();

   void updateData(const double dt = 0.0) override;
   void reset() override;

protected:
   // generic controller
   virtual void controller(const double dt = 0.0);

   AbstractBehavior* getBehavior() const          { return behavior; }
   void setBehavior(AbstractBehavior* const);

   AbstractState* getState() const                { return state; }
   void setState(AbstractState* const);

   virtual void initActor();

   base::Component* getActor();
   void setActor(base::Component* const myActor);

private:
   AbstractBehavior* behavior{};
   AbstractState* state{};
   safe_ptr<base::Component> myActor;

private:
   // slot table helper methods
   bool setSlotBehavior(AbstractBehavior* const);
   bool setSlotState(AbstractState* const);
};

inline void Agent::setActor(base::Component* const actor)      { myActor = actor; return; }
inline base::Component* Agent::getActor()                      { return myActor; }


//------------------------------------------------------------------------------
// Class: Agent
//
// Description: Generic agent class to control a component - the agent's "actor"
// - a derived agent class that performs its actions in the TC thread
//
// Factory name: UbfAgentTC
//------------------------------------------------------------------------------
class AgentTC : public Agent
{
   DECLARE_SUBCLASS(AgentTC, Agent)

public:
   AgentTC();

   void updateTC(const double dt = 0.0) override;
};

}
}
}

#endif

