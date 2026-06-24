#pragma once

#include <vector>

#include "mixr/base/Object.hpp"
#include "mixr/base/functors/Function.hpp"

namespace mixr {
namespace base {

class FStorage;

//------------------------------------------------------------------------------
// Class: Polynomial
// Description: Polynomial function
//                f(x) = a0 + a1*x + a2*x^2 + ... + aN*x^N
//
// Factory names: Polynomial
// Slots:
//    coefficients   <base::List>  ! Constant coefficients vector: [ a0 a1 a2 ... aN ]
//
// Notes
//    1) The degree of the polynomial is determined by the size of the coefficients vector.
//
//          coefficients     degree            result
//          ------------    --------     --------------------------------
//             none            < 0        0
//              1               0         a0
//              2               1         a0 + a1 * x
//              3               2         a0 + a1 * x + a2 * x^2
//              M             N = M-1     a0 + a1 * x + a2 * x^2 + ... + aN * x^N
//
//    2) Storage is not used.
//
//------------------------------------------------------------------------------
class Polynomial : public Func1
{
   DECLARE_SUBCLASS(Polynomial, Func1)

public:
   // Highest allowed degree of polynomial
   static constexpr int MAX_DEGREE{32};

public:
   Polynomial();

   int getDegree() const                  { return m_coefficients.size() - 1; }
   const double* getCoefficients() const  { return m_coefficients.data(); }

   double f(const double x) const override;

   bool setCoefficients(const std::vector<double>&);

private:
   static constexpr int MAX_COEFF{MAX_DEGREE+1};

   std::vector<double> m_coefficients{MAX_COEFF}; // Constant coefficients vector

protected:
   // slot table helper methods
   virtual bool setSlotCoefficients(std::shared_ptr<const std::vector<double>>);
   virtual std::shared_ptr<const std::vector<double>> getSlotCoefficients() const;
};

}
}
