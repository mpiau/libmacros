#include "libmacros/libmacros.h"

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

int main(void)
{
   char const array1[255] = {};
   int  const array2[16] = {};

   assert(arrayCapacity(array1) == 255);
   assert(arrayCapacity(array2) == 16);

   print_usings();

   return 0;
}
