#include "libmacros/libmacros.h"
#include "libmacros/macro_utils.h"

#include <assert.h>
#include <stdio.h>


[[nodiscard]] static inline
char const *using_to_str(bool const value)
{
   return value ? "IN_USE" : "NOT_IN_USE";
}

static void print_usings(void)
{
   // Note:
   // %-20s because 20 is the largest define (OS_ENDIANNESS_LITTLE).
   // It's used to align properly everything on the console.
#define PRINT_USING(pUsing)   \
   printf("|- %-20s = %s\n", #pUsing, using_to_str(USING(pUsing)))

   printf("Compilers\n");
   PRINT_USING(COMPILER_CLANG);
   PRINT_USING(COMPILER_GCC);
   PRINT_USING(COMPILER_MSVC);

   printf("\nOperating System\n");
   PRINT_USING(OS_WINDOWS);
   PRINT_USING(OS_MAC);
   PRINT_USING(OS_IOS);
   PRINT_USING(OS_ANDROID);
   PRINT_USING(OS_GNU);
   PRINT_USING(OS_APPLE);
   PRINT_USING(OS_LINUX);
   PRINT_USING(OS_MOBILE);
   PRINT_USING(OS_PC);

   printf("\nOperating System - Architecture\n");
   PRINT_USING(OS_ARCH_32_BITS);
   PRINT_USING(OS_ARCH_64_BITS);

   printf("\nOperating System - Endianness\n");
   PRINT_USING(OS_ENDIANNESS_LITTLE);
   PRINT_USING(OS_ENDIANNESS_BIG);

#undef PRINT_USING
}

enum Signed   : int      { Signed_VALUE };
enum Unsigned : unsigned { Unsigned_VALUE };

static_assert(type_is_signed(char));
static_assert(type_is_signed(int));
static_assert(type_is_signed(long const));
static_assert(type_is_signed(float));
static_assert(type_is_signed(double volatile));
static_assert(type_is_signed(_BitInt(16)));
static_assert(type_is_signed(enum Signed const volatile));

static_assert(type_is_unsigned(unsigned char));
static_assert(type_is_unsigned(unsigned int const));
static_assert(type_is_unsigned(unsigned long volatile));
static_assert(type_is_unsigned(bool const volatile));
static_assert(type_is_unsigned(unsigned _BitInt(16)));
static_assert(type_is_unsigned(enum Unsigned));


int main(void)
{
   char const array1[255] = {};
   int  volatile array2[16] = {};
   char const volatile array3[8] = {};

   static_assert(array_capacity(array1) == 255);
   static_assert(var_is_const(array1) && var_is_not_volatile(array1));

   static_assert(array_capacity(array2) == 16);
   static_assert(var_is_not_const(array2) && var_is_volatile(array2));

   static_assert(array_capacity(array3) == 8);
   static_assert(var_is_const_volatile(array3));

   print_usings();

   return 0;
}
