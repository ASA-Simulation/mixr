
#include "mixr/base/ubf/Arbiter.hpp"
#include "mixr/base/ubf/AbstractAction.hpp"

#include "mixr/base/Pair.hpp"
#include "mixr/base/PairStream.hpp"

namespace mixr {
namespace base {
namespace ubf {

IMPLEMENT_SUBCLASS(Arbiter, "UbfArbiter")
EMPTY_COPYDATA(Arbiter)

BEGIN_SLOTTABLE(Arbiter)
   "behaviors"                    //  1) behaviors
END_SLOTTABLE(Arbiter)

BEGIN_SLOT_MAP(Arbiter)
   ON_SLOT(1, setSlotBehaviors, base::PairStream)
END_SLOT_MAP()

Arbiter::Arbiter()
{
   STANDARD_CONSTRUCTOR()
   behaviors = new base::List();
}

void Arbiter::deleteData()
{
   // unref behaviors
   if ( behaviors!=nullptr ) { behaviors->unref();   behaviors = nullptr; }
}

//------------------------------------------------------------------------------
// genAction() - generate an action
//------------------------------------------------------------------------------
AbstractAction* Arbiter::genAction(const AbstractState* const state, const double dt)
{
   // create list for action set
   const auto actionSet = new base::List();

   // fill out list of recommended actions by behaviors
   base::List::Item* item{behaviors->getFirstItem()};
   while (item != nullptr) {
      // get a behavior
      const auto behavior = static_cast<AbstractBehavior*>(item->getValue());
      // generate action, we have reference
      AbstractAction* action{behavior->genAction(state, dt)};
      if (action != nullptr) {
         // add to action set
         actionSet->addTail(action);
         // unref our action reference
         action->unref();
      }
      // goto behavior
      item = item->getNext();
   }

   // given the set of recommended actions, the arbiter
   // decides what action to take
   AbstractAction* complexAction{genComplexAction(actionSet)};

   // done with action set
   actionSet->unref();

   // return action to perform
   return complexAction;
}


//------------------------------------------------------------------------------
// Default: select the action with the highest vote
//------------------------------------------------------------------------------
AbstractAction* Arbiter::genComplexAction(base::List* const actionSet)
{
   AbstractAction* complexAction{};
   int maxVote{};

   // process entire action set
   base::List::Item* item{actionSet->getFirstItem()};
   while (item != nullptr) {

      // Is this action's vote higher than the previous?
      const auto action = static_cast<AbstractAction*>(item->getValue());
      if (maxVote==0 || action->getVote() > maxVote) {

         // Yes ...
         if (complexAction != nullptr) complexAction->unref();
         complexAction = action;
         complexAction->ref();
         maxVote = action->getVote();
      }

      // next action
      item = item->getNext();
   }

   if (maxVote > 0 && isMessageEnabled(MSG_DEBUG))
      std::cout << "Arbiter: chose action with vote= " << maxVote << std::endl;

   // Use our vote value; if its been set
   if (getVote() > 0 && complexAction != nullptr) {
      complexAction->setVote(getVote());
   }

   // complexAction will have the vote value of whichever component action was selected
   return complexAction;
}

//------------------------------------------------------------------------------
// addBehavior() - add a new behavior
//------------------------------------------------------------------------------
void Arbiter::addBehavior(AbstractBehavior* const x)
{
   behaviors->addTail(x);
   x->container(this);
}

//------------------------------------------------------------------------------
// Slot functions
//------------------------------------------------------------------------------

bool Arbiter::setSlotBehaviors(base::PairStream* const x)
{
   bool ok{true};

   // First, make sure they are all behaviors
   {
      base::List::Item* item{x->getFirstItem()};
      while (item != nullptr && ok) {
         const auto pair = static_cast<base::Pair*>(item->getValue());
         item = item->getNext();
         const auto b = dynamic_cast<AbstractBehavior*>( pair->object() );
         if (b == nullptr) {
            // Item is NOT a behavior
            std::cerr << "setSlotBehaviors: slot: " << *pair->slot() << " is NOT of a Behavior type!" << std::endl;
            ok = false;
         }
      }
   }

   // next, add behaviors to our list
   if (ok) {
      base::List::Item* item{x->getFirstItem()};
      while (item != nullptr) {
         const auto pair = static_cast<base::Pair*>(item->getValue());
         item = item->getNext();
         const auto b = static_cast<AbstractBehavior*>(pair->object());
         addBehavior(b);
      }
   }

   return ok;
}

}
}
}
