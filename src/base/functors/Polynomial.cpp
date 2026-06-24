#include <iostream>

#include "mixr/base/functors/Polynomial.hpp"


namespace mixr {
namespace base {

IMPLEMENT_SUBCLASS(Polynomial, "Polynomial")
EMPTY_COPYDATA(Polynomial)
EMPTY_DELETEDATA(Polynomial)

BEGIN_SLOTTABLE(Polynomial)
    "coefficients"   // 1) Constant coefficients vector: [ a0 a1 a2 ... aN ]
END_SLOTTABLE(Polynomial)

BEGIN_SLOT_MAP(Polynomial)
    ON_SLOT( 1, setSlotCoefficients, const std::vector<double>)
END_SLOT_MAP()

Polynomial::Polynomial()
{
   STANDARD_CONSTRUCTOR()
}

//------------------------------------------------------------------------------
// The polynomial function
//------------------------------------------------------------------------------
double Polynomial::f(const double x) const
{
   double result {0.0};

   double xx {1.0};
   for (int i = 0; i < m_coefficients.size(); i++) {
      result += (m_coefficients[i] * xx);
      xx *= x;
   }

   return result;
}

//------------------------------------------------------------------------------
// Set functions
//------------------------------------------------------------------------------
bool Polynomial::setCoefficients(const std::vector<double>& coeffs)
{
   bool ok {false};

   if (coeffs.size() > MAX_COEFF) {
      if (isMessageEnabled(MSG_ERROR)) {
         std::cerr << "Polynomial::setCoefficients(): ERROR; too many coefficients; max is " << MAX_COEFF << std::endl;
      }
   }
   
   // 
   m_coefficients = coeffs;
   ok = true;

   return ok;
}

bool Polynomial::setSlotCoefficients(std::shared_ptr<const std::vector<double>> msg)
{
   bool ok {false};

   if (msg == nullptr) {
      // Just remove the old ...
      ok = setCoefficients(std::vector<double>{});
   }
   else 
   {
      ok = setCoefficients(*msg);
   }

   return ok;
}

std::shared_ptr<const std::vector<double>> Polynomial::getSlotCoefficients() const {
   return std::make_shared<const std::vector<double>>(m_coefficients);
}

}
}
