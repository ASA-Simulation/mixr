
#ifndef __mixr_recorder_InputHandler_H__
#define __mixr_recorder_InputHandler_H__

#include "mixr/simulation/AbstractRecorderComponent.hpp"

namespace mixr {
namespace recorder {
class DataRecordHandle;

//------------------------------------------------------------------------------
// Class: InputHandler
// Description: Read and parse data records from an input source
//------------------------------------------------------------------------------
class InputHandler : public simulation::AbstractRecorderComponent
{
    DECLARE_SUBCLASS(InputHandler, simulation::AbstractRecorderComponent)

public:
   InputHandler();

   // Read one data record; returns zero if no record is available
   const DataRecordHandle* readRecord();

protected:
   // Read one record from our data source
   // -- Must be implemented by our derived classes
   virtual const DataRecordHandle* readRecordImp() =0;
};

}
}

#endif
