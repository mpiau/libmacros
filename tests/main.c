#include "libmacros/libmacros.h"
#include <assert.h>


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
   return 0;
}
