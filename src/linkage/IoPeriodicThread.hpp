#pragma once

#include "mixr/base/threads/PeriodicThread.hpp"

namespace mixr {
namespace base { class Component; }
namespace linkage {

class IoPeriodicThread final : public base::PeriodicThread
{
   public: IoPeriodicThread(base::Component* const parent, const double rate);
   private: unsigned long userFunc(const double dt) final;
};

}

}

