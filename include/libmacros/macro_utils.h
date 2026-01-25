#pragma once

#include "macro_compilers.h"


//================================================================================================
// Array Capacity
//================================================================================================

/*
   If you want to use that in a loop, please consider creating a const variable holding the result
   instead of calling the macro each time. You will save some CPU cycles.
*/
#define array_capacity(pArray) (sizeof(pArray) / sizeof(pArray[0]))


//================================================================================================
// Type related checks
//================================================================================================

#define type_is_unsigned(T)        (((T)-1) > 0)
#define type_is_not_unsigned(T)    (!type_is_unsigned(T))

#define type_is_signed(T)          (((T)-1) < 0)
#define type_is_not_signed(T)      (!type_is_signed(T))

#define types_size_equal(T, U)     (sizeof(T) == sizeof(U))
#define types_size_not_equal(T, U) (!types_size_equal(T, U))


//================================================================================================
// Variable related checks
//================================================================================================

#define var_is_const(var)                \
   _Generic(                             \
      &(var), typeof(var) const *: true, \
      default: false                     \
   )

#define var_is_volatile(var)                \
   _Generic(                                \
      &(var), typeof(var) volatile *: true, \
      default: false                        \
   )

#define var_is_not_const(var)           (!var_is_const(var))
#define var_is_not_volatile(var)        (!var_is_volatile(var))
#define var_is_const_volatile(var)      (var_is_const(var) && var_is_volatile(var))
#define var_is_not_const_volatile(var)  (!var_is_const_volatile(var))
