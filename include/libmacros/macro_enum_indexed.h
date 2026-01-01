#pragma once

// Prerequisites:
// ==============
// - Values inside the enum MUST be contiguous
// - Enum are written with the comma at the beginning of the line, not the end. It's a personal
// style choice.

// Note:
// I'm experimenting a bit with enums as they provide a clean interface for related constants.
// However, the support for it is quite primitive in C. I may think about a enum-generator script
// in order to automatically generate functions (like get the value name) and remove some defines.
// This way, we could have a file with the enum list, and then generate associated .h/.c files.


// ===============================================================================================
// Code Generation (CG)
// ===============================================================================================

// This macro will generate the following members:
// [...]_Count (Number of members between first and last)
// Note: It is assumed that First <= Last
// [...]_First -> [...]_Last

#define CG_ENUM_INDEXED_MEMBERS(pEnum, pFirst, pLast)   \
   , pEnum##_Count = (pLast - pFirst) + 1 \
   , pEnum##_First = pFirst               \
   , pEnum##_Last  = pLast

#define CG_ENUM_INDEXED_RANGE_MEMBERS(pEnum, pRange, pFirst, pLast)   \
   , pEnum##_##pRange##_Count = (pLast - pFirst) + 1 \
   , pEnum##_##pRange##_First = pFirst               \
   , pEnum##_##pRange##_Last  = pLast


// ===============================================================================================
// Associated helpers
// ===============================================================================================

// -----------------------------------------------------------------------------------------------
// Value validity
// -----------------------------------------------------------------------------------------------

// Validate if the given value is inside the indexed enum.
#define enum_indexed_is_valid(pVar, pEnum) \
   ( !(pVar < pEnum##_First || pVar > pEnum##_Last) )

// Validate if the given value is inside the indexed enum range.
#define enum_indexed_is_valid_range(pVar, pEnum, pRange) \
   ( !(pVar < pEnum##_##pRange##_First || pVar > pEnum##_##pRange##_Last) )


// -----------------------------------------------------------------------------------------------
// Foreach keyword
// -----------------------------------------------------------------------------------------------

// Iterate through an indexed enum values.
#define foreach_enum_indexed(pVar, pEnum) \
   for (pEnum pVar = pEnum##_First; pVar <= pEnum##_Last; ++pVar)

// Iterate through a particular named range of values inside an indexed enum.
#define foreach_enum_indexed_range(pVar, pEnum, pRange) \
   for (pEnum pVar = pEnum##_##pRange##_First; pVar <= pEnum##_##pRange##_Last; ++pVar)


// ===============================================================================================
// Example(s)
// ===============================================================================================

// enum Test
// {
//      Test_LETTER_ONE
//    , Test_LETTER_TWO
//    , Test_LETTER_THREE
//    , Test_NUMBER_FOUR
//    , Test_NUMBER_FIVE

//    // Complete enum range
//    CG_ENUM_INDEXED_MEMBERS(Test, Test_LETTER_ONE, Test_NUMBER_FIVE)

//    // Sub range to isolate letters together
//    CG_ENUM_INDEXED_RANGE_MEMBERS(Test, Letter, Test_LETTER_ONE, Test_LETTER_THREE)
// };
// typedef enum Test Test;

// static_assert(Test_Letter_Count == 3);
// static_assert(Test_Count == 5);

// #include <assert.h>
// int main()
// {
//    foreach_enum_indexed(idx, Test)
//    {
//       assert(enum_indexed_is_valid(idx, Test));
//       // Will iterate from Test_LETTER_ONE -> Test_NUMBER_FIVE
//    }
//    foreach_enum_indexed_range(idx, Test, Letter)
//    {
//       assert(enum_indexed_is_valid_range(idx, Test, Letter));
//       // Will iterate from Test_LETTER_ONE -> Test_LETTER_THREE
//    }
//    return 0;
// }
