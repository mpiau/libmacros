#pragma once

// Example of usage:
// -----------------
//
// #if USING(OS_WINDOWS)
// [...]
// #else
// [...]
// #endif
//

#include "macro_conditional_compilation.h"


//================================================================================================
// Operating System (OS) Identification
//================================================================================================

#if defined( WIN32 ) || defined( _WIN32 ) || defined( __WIN32__ ) || defined( __NT__ )
#  define OS_WINDOWS IN_USE
#  define OS_APPLE   NOT_IN_USE
#  define OS_ANDROID NOT_IN_USE
#  define OS_LINUX   NOT_IN_USE

#elif defined(__APPLE__)
#  define OS_WINDOWS NOT_IN_USE
#  define OS_APPLE   IN_USE
#  define OS_ANDROID NOT_IN_USE
#  define OS_LINUX   NOT_IN_USE

#elif defined(__ANDROID__)
#  define OS_WINDOWS NOT_IN_USE
#  define OS_APPLE   NOT_IN_USE
#  define OS_ANDROID IN_USE
#  define OS_LINUX   NOT_IN_USE

#elif defined(__gnu_linux__) // Don't use __linux__ as Android also defines it.
#  define OS_WINDOWS NOT_IN_USE
#  define OS_APPLE   NOT_IN_USE
#  define OS_ANDROID NOT_IN_USE
#  define OS_LINUX   IN_USE

#else
#  error The Operating System used to compile this file is not currently supported.

#endif


//------------------------------------------------------------------------------------------------

// Ensures that only one of the macros is defined as IN_USE.
static_assert(USING(OS_WINDOWS) + USING(OS_APPLE) + USING(OS_ANDROID) + USING(OS_LINUX) == 1);
