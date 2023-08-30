
#ifndef __mixr_base_util_volume_H__
#define __mixr_base_util_volume_H__

namespace mixr {
namespace base {
namespace volume {

// conversion constants
const double CM2CFT = 35.3146667215f;   // CubicMeters => CubicFeet
const double CFT2CM = (1 / CM2CFT);     // CubicFeet => CubicMeters
const double CM2CIN = 61023.7440947f;   // CubicMeters => CubicInches
const double CIN2CM = (1 / CM2CIN);     // CubicInches => CubicMeters
const double CM2L = 1000.0f;            // CubicMeters => Liters
const double L2CM = (1 / CM2L);         // Liters => CubicMeters

// conversion routines
inline double cubicMetersToFeet(const double v)   { return v * CM2CFT; }
inline double cubicFeetToMeters(const double v)   { return v * CFT2CM; }

inline double litersToCubicMeters(const double v) { return v * L2CM; }
inline double cubicMetersToLiters(const double v) { return v * CM2L; }

inline double cubicFeetToInches(const double v)   { return (v * CFT2CM) * CM2CIN; }
inline double cubicInchesToFeet(const double v)   { return (v * CIN2CM) * CM2CFT; }

}
}
}

#endif
