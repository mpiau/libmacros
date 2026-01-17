#pragma once

#include "macro_conditional_compilation.h"


//================================================================================================
// Compiler Identification
//================================================================================================

#if defined __clang__
#  define COMPILER_CLANG   IN_USE
#  define COMPILER_GCC     NOT_IN_USE
#  define COMPILER_MSVC    NOT_IN_USE

#elif defined __GNUC__ || defined __GNUG__
#  define COMPILER_CLANG   NOT_IN_USE
#  define COMPILER_GCC     IN_USE
#  define COMPILER_MSVC    NOT_IN_USE

#elif defined _MSC_VER
#  define COMPILER_CLANG   NOT_IN_USE
#  define COMPILER_GCC     NOT_IN_USE
#  define COMPILER_MSVC    IN_USE

#else
#  error The compiler used on this file is not currently supported.

#endif


//------------------------------------------------------------------------------------------------

// Ensures that only one of the macros is defined as IN_USE.
static_assert(USING(COMPILER_CLANG) + USING(COMPILER_GCC) + USING(COMPILER_MSVC) == 1);
