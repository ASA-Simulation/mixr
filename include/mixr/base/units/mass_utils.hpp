
#ifndef __mixr_base_util_mass_H__
#define __mixr_base_util_mass_H__

namespace mixr {
namespace base {
namespace mass {

// conversion constant
const double KG2G = 1000.0;            // KiloGrams => Grams
const double G2KG = (1 / KG2G);        // Grams => KiloGrams
const double KG2SL = 0.06852176585f;   // KiloGrams => Slugs
const double SL2KG = (1 / KG2SL);      // Slugs => KiloGrams
const double KG2PM = 2.2046f;          // KiloGrams => PoundsMass
const double PM2KG = (1 / KG2PM);      // PoundsMass => KiloGrams

// conversions between Masss
inline double gramsToKiloGrams(const double v) { return v * G2KG; }
inline double gramsToSlugs(const double v)     { return (v * G2KG) * KG2SL; }
inline double kiloGramsToGrams(const double v) { return v * KG2G; }
inline double kiloGramsToSlugs(const double v) { return v * KG2SL;}
inline double slugsToGrams(const double v)     { return (v * SL2KG) * KG2G; }
inline double slugsToKiloGrams(const double v) { return v * SL2KG; }

}
}
}

#endif
