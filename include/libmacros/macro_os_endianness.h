#pragma once

#include "macro_os.h"


//================================================================================================
// Endianness Identification
//================================================================================================

#if USING(OS_WINDOWS)
// We are assuming that we are in little endianness on Windows.
#   define OS_ENDIANNESS_LITTLE  IN_USE
#   define OS_ENDIANNESS_BIG     NOT_IN_USE
#else // #if USING(OS_WINDOWS)


#if USING(OS_LINUX)
#   include <endian.h>

#elif USING(OS_APPLE)
#   include <machine/endian.h>

#endif


#if defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#   define OS_ENDIANNESS_LITTLE  NOT_IN_USE
#   define OS_ENDIANNESS_BIG     IN_USE

#elif defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
#   define OS_ENDIANNESS_LITTLE  IN_USE
#   define OS_ENDIANNESS_BIG     NOT_IN_USE

#else
#   error Impossible to detect the Endianness of the current system.

#endif


#endif // #else // #if USING(OS_WINDOWS)


//------------------------------------------------------------------------------------------------

// Ensures that only one of the macros is defined as IN_USE.
static_assert(USING(OS_ENDIANNESS_LITTLE) + USING(OS_ENDIANNESS_BIG) == 1);
