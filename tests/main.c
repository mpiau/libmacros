#include "libmacros/libmacros.h"

#include <assert.h>
#include <stdio.h>


enum Test
{
     Test_LETTER_ONE
   , Test_LETTER_TWO
   , Test_LETTER_THREE
   , Test_NUMBER_FOUR
   , Test_NUMBER_FIVE

   // Complete enum range
   CG_ENUM_INDEXED_MEMBERS(Test, Test_LETTER_ONE, Test_NUMBER_FIVE)

   // Sub range to isolate letters together
   CG_ENUM_INDEXED_RANGE_MEMBERS(Test, Letter, Test_LETTER_ONE, Test_LETTER_THREE)
};
typedef enum Test Test;


static_assert(Test_Letter_Count == 3);
static_assert(Test_Count == 5);


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
   PRINT_USING(OS_APPLE);
   PRINT_USING(OS_ANDROID);
   PRINT_USING(OS_GNU);
   PRINT_USING(OS_LINUX);

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
   foreach_enum_indexed(idx, Test)
   {
      assert(enum_indexed_is_valid(idx, Test));
   }
   foreach_enum_indexed_range(idx, Test, Letter)
   {
      bool const inRange = (idx == Test_LETTER_ONE || idx == Test_LETTER_TWO || idx == Test_LETTER_THREE);
      assert(enum_indexed_is_valid_range(idx, Test, Letter) == inRange);
   }

   char array1[255];
   int  array2[16];

   assert(sizeofArrayElem(array1) == 255);
   assert(sizeofArrayElem(array2) == 16);

   print_usings();

   return 0;
}
