//------------------------------------------------------------------------------
// Support functions (MinGW unique)
//------------------------------------------------------------------------------

#include <sys/timeb.h>
#include <sys/time.h>
#include <ctime>

namespace mixr {
namespace base {

//------------
// sleep for 'msec' milliseconds
//------------
void msleep(const unsigned int msec)
{
   Sleep(msec);
}

//------------
// Computer time (seconds)
//------------
double getComputerTime()
{
   return static_cast<double>(timeGetTime())/1000.0;
}

//------------
// Get UTC time since midnight (00:00:00), January 1, 1970
//------------
void getTime(
      unsigned long* const sec,  // (OUT) whole seconds
      unsigned long* const uSec  // (OUT) microseconds seconds
   )
{
   timeval tv;
   gettimeofday(&tv,NULL);

   if (sec != nullptr) *sec = tv.tv_sec;
   if (uSec != nullptr) *uSec = tv.tv_usec;
}

//------------
// Convert seconds since midnight (00:00:00), January 1, 1970 to year:month:day:hour:minute:second
//------------
bool convertSec2Ymdhms(
      const unsigned long seconds,  // (IN) whole seconds since midnight (00:00:00), January 1, 1970
      unsigned int* const year,     // (OUT) year YYYY
      unsigned int* const month,    // (OUT) month of the year [ 1 .. 12 ]
      unsigned int* const day,      // (OUT) day of the month   [ 1 .. 31 ]
      unsigned int* const hour,     // (OUT) hours since midnight  [ 0 .. 23 ]
      unsigned int* const min,      // (OUT) minutes after the hour [ 0 .. 59 ]
      unsigned int* const sec       // (OUT) seconds after the minute [ 0 .. 59 ]
   )
{
   time_t tt{static_cast<time_t>(seconds)};
   struct tm* tmx{gmtime( &tt )};

   if (year != nullptr)  *year = tmx->tm_year + 1900;
   if (month != nullptr) *month = tmx->tm_mon + 1;
   if (day != nullptr)   *day = tmx->tm_mday;
   if (hour != nullptr)  *hour = tmx->tm_hour;
   if (min != nullptr)   *min = tmx->tm_min;
   if (sec != nullptr)   *sec = tmx->tm_sec;
   return true;
}

//------------
// Convert year:month:day:hour:minute:second to seconds since midnight (00:00:00), January 1, 1970
//------------
bool convertYmdhms2Sec(
      const unsigned int year,      // (IN) year YYYY
      const unsigned int month,     // (IN) month of the year [ 1 .. 12 ]
      const unsigned int day,       // (IN) day of the month   [ 1 .. 31 ]
      const unsigned int hour,      // (IN) hours since midnight  [ 0 .. 23 ]
      const unsigned int min,       // (IN) minutes after the hour [ 0 .. 59 ]
      const unsigned int sec,       // (IN) seconds after the minute [ 0 .. 59 ]
      unsigned long* const seconds  // (OUT) whole seconds since midnight (00:00:00), January 1, 1970
   )
{
   bool ok{};
   if (seconds != nullptr) {
      struct tm tmx;
      tmx.tm_year = (year - 1900);
      tmx.tm_mon  = (month - 1);
      tmx.tm_mday = day;
      tmx.tm_hour = hour;
      tmx.tm_min  = min;
      tmx.tm_sec  = sec;
      tmx.tm_isdst = 0;
      tmx.tm_wday = -1;
      tmx.tm_yday = -1;

      *seconds = mktime(&tmx);
      ok = true;
   }
   return ok;
}

}
}

