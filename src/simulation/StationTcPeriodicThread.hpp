#pragma once

#include "mixr/base/threads/PeriodicThread.hpp"

namespace mixr {
namespace simulation {

// ---
// Time-critical thread
// ---
class StationTcPeriodicThread final : public base::PeriodicThread
{
   public: StationTcPeriodicThread(base::Component* const parent, const double rate);
   private: unsigned long userFunc(const double dt) final;
};

}

}

