#pragma once

#include "mixr/base/threads/PeriodicThread.hpp"

}
}

// Background thread
// ---
class StationBgPeriodicThread final : public base::PeriodicThread
{
   public: StationBgPeriodicThread(base::Component* const parent, const double rate);
   private: unsigned long userFunc(const double dt) final;
};

}
}



#endif
