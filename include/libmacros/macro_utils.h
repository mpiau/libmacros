#pragma once

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

/*
   When I wrote this code and then checked the differences between an int and a const enum : int,
   I was surprised to see that it worked on GCC (not Clang, which was expected outcome).
   It seems that GCC still uses the underlying type of the enum and for whatever reason, doesn't
   care about the const difference ? And making dummy pointers don't change the outcome.
   I also tried to use some builtins like __builtin_types_compatible_p but it doesn't take into
   account const/volatile.
   I'll disable that specific macro for now, the time to find a proper solution.
*/
#if 0
#define types_same(T, U) \
   _Generic(             \
      T, U: true,        \
      default: false     \
   )
#define types_not_same(T, U) (!types_same(T, U))
#endif


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
