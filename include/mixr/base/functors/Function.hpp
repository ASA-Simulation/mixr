#pragma once

#include "mixr/base/Object.hpp"

namespace mixr {
namespace base {

class FStorage;
class Table;

//------------------------------------------------------------------------------
// Class: Function
//
// Description: Base for the derived, multi-dimensional function classes.
//
// Notes:
//    1) Use the storageFactory() function to create the FStorage object that
//       will maintain the previous function call values (i.e., integration).
//
//   virtual FStorage* storageFactory() const;
//       Data storage factory (pre-ref()'d)
//   virtual bool setSlotLfiTable(std::shared_ptr<const Table> msg);
//       Set Slot Tables
//
// Slots:
//    table    <Table>     ! Optional LFI table
//
//------------------------------------------------------------------------------
class Function : public Object
{
   DECLARE_SUBCLASS(Function, Object)

public:
   Function() = default;

   virtual std::vector<double> map(const std::vector<double>&& iv) const = 0;
};



/**
 * Class: Func1
 * Description: Generic 1-Dimensional function; f(iv1)
 */
class Func1 : public Function
{
   DECLARE_SUBCLASS(Func1, Function)
public:
   Func1() = default;

   std::vector<double> map(const std::vector<double>&& iv) const override { 
      return {
         f(iv[0])
      }; 
   }

   virtual double f(const double iv1) const  = 0;
};

/**
 * Class: Func2
 * Description: Generic 2-Dimensional function; f(iv1, iv2)
 */
class Func2 : public Function
{
   DECLARE_SUBCLASS(Func2, Function)
public:
   Func2() = default;

   std::vector<double> map(const std::vector<double>&& iv) const override { 
      return {
         f(iv[0], iv[1])
      }; 
   }

   virtual double f(const double iv1, const double iv2) const = 0;
};

/**
 * Class: Func3
 * Description: Generic 3-Dimensional function; f(iv1, iv2, iv3)
 */
class Func3 : public Function
{
   DECLARE_SUBCLASS(Func3, Function)
public:
   Func3() = default;

   std::vector<double> map(const std::vector<double>&& iv) const override { 
      return {
         f(iv[0], iv[1], iv[2])
      }; 
   }

   virtual double f(const double iv1, const double iv2, const double iv3) const = 0;
};

/**
 * Class: Func4
 * Description: Generic 4-Dimensional function; f(iv1, iv2, iv3, iv4)
 */
class Func4 : public Function
{
   DECLARE_SUBCLASS(Func4, Function)
public:
   Func4() = default;

   std::vector<double> map(const std::vector<double>&& iv) const override { 
      return {
         f(iv[0], iv[1], iv[2], iv[3])
      }; 
   }

   virtual double f(const double iv1, const double iv2, const double iv3, const double iv4) const = 0;
};

/**
 * Class: Func5
 * Description: Generic 5-Dimensional function; f(iv1, iv2, iv3, iv4, iv5)
 */
class Func5 : public Function
{
   DECLARE_SUBCLASS(Func5, Function)
public:
   Func5() = default;

   std::vector<double> map(const std::vector<double>&& iv) const override { 
      return {
         f(iv[0], iv[1], iv[2], iv[3], iv[4])
      }; 
   }

   virtual double f(const double iv1, const double iv2, const double iv3, const double iv4, const double iv5) const = 0;
};


}
}
