
#include "mixr/base/numeric/Complex.hpp"
#include "mixr/base/numeric/Number.hpp"

#include <iostream>
#include <iomanip>
#include <cmath>

namespace mixr {
namespace base {

IMPLEMENT_SUBCLASS(Complex, "Complex")
EMPTY_DELETEDATA(Complex)

BEGIN_SLOTTABLE(Complex)
   "imag",      // 1: imaginary component
END_SLOTTABLE(Complex)

BEGIN_SLOT_MAP(Complex)
   ON_SLOT(1, setSlotImaginary, Number)
END_SLOT_MAP()

Complex::Complex()
{
   STANDARD_CONSTRUCTOR()
}

Complex::Complex(const double r) : Number(r)
{
   STANDARD_CONSTRUCTOR()
}

Complex::Complex(const double r, const double i) : Number(r), imag(i)
{
   STANDARD_CONSTRUCTOR()
}

void Complex::copyData(const Complex& org, const bool)
{
   BaseClass::copyData(org);

   imag = org.imag;
}

//------------------------------------------------------------------------------
// Output Functions
//------------------------------------------------------------------------------
void Complex::showComplex(const int decpnt) const
{
   std::ios_base::fmtflags oldFmtFlgs =  std::cout.flags();
   std::streamsize oldprec = std::cout.precision();

   std::cout << std::setprecision(decpnt) << std::setiosflags(std::ios::fixed);
   std::cout << getReal() << " + j*" << getImag() << std::endl;

   std::cout.setf(oldFmtFlgs);
   std::cout << std::setprecision(oldprec);
}

void Complex::showPhasor(const int decpnt) const
{
   std::ios_base::fmtflags oldFmtFlgs =  std::cout.flags();
   std::streamsize oldprec = std::cout.precision();

   std::cout << std::setprecision(decpnt) << std::setiosflags(std::ios::fixed);
   std::cout << "<" << this->getMag() << ", " << this->getArg() << ">" << std::endl;

   std::cout.setf(oldFmtFlgs);
   std::cout << std::setprecision(oldprec);
}

std::ostream& operator<<(std::ostream& sout, const Complex& z)
{
   std::ios_base::fmtflags oldFmtFlgs =  sout.flags();
   std::streamsize oldprec = sout.precision();

   const int decpnt = 2;
   sout << std::setprecision(decpnt) << std::setiosflags(std::ios::fixed);
   sout << z.getReal() << " + j*" << z.getImag();

   sout.setf(oldFmtFlgs);
   sout << std::setprecision(oldprec);

   return sout;
}

//------------------------------------------------------------------------------
// Slot functions
//------------------------------------------------------------------------------
bool Complex::setSlotImaginary(const Number* const msg)
{
    double value{msg->getDouble()};
    const bool ok{setImag( value )};
    if (!ok) std::cerr << "Complex::setSlotImaginary: invalid entry(" << value << ")" << std::endl;
    return ok;
}

}
}

