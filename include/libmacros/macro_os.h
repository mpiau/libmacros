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

#if defined WIN32 || defined _WIN32 || defined __WIN32__ || defined __NT__
#  define OS_WINDOWS IN_USE
#  define OS_MAC     NOT_IN_USE
#  define OS_IOS     NOT_IN_USE
#  define OS_ANDROID NOT_IN_USE
#  define OS_GNU     NOT_IN_USE

#elif defined __APPLE__ && defined __MACH__
#  include <TargetConditionals.h>
#  define OS_WINDOWS NOT_IN_USE
#  if TARGET_OS_IPHONE == 1
#     define OS_IOS  IN_USE
#     define OS_MAC  NOT_IN_USE
#  elif TARGET_OS_MAC == 1
#     define OS_IOS  NOT_IN_USE
#     define OS_MAC  IN_USE
#  else
#     error Failure to identify the specific Apple OS Target used.
#  endif
#  define OS_ANDROID NOT_IN_USE
#  define OS_GNU     NOT_IN_USE

#elif defined __ANDROID__
#  define OS_WINDOWS NOT_IN_USE
#  define OS_MAC     NOT_IN_USE
#  define OS_IOS     NOT_IN_USE
#  define OS_ANDROID IN_USE
#  define OS_GNU     NOT_IN_USE

#elif defined __gnu_linux__
// Don't use __linux__ as Android also defines it.
#  define OS_WINDOWS NOT_IN_USE
#  define OS_MAC     NOT_IN_USE
#  define OS_IOS     NOT_IN_USE
#  define OS_ANDROID NOT_IN_USE
#  define OS_GNU     IN_USE

#else
#  error The Operating System used to compile this file is not currently supported.

#endif


//------------------------------------------------------------------------------------------------

#define OS_APPLE     USING(OS_IOS) || USING(OS_MAC)
#define OS_LINUX     USING(OS_GNU) || USING(OS_ANDROID)

#define OS_MOBILE    USING(OS_IOS) || USING(OS_ANDROID)
#define OS_PC        USING(OS_GNU) || USING(OS_WINDOWS) || USING(OS_MAC)


//------------------------------------------------------------------------------------------------

// Ensures that only one of the macros is defined as IN_USE.
static_assert(
   USING(OS_WINDOWS) + USING(OS_IOS) + USING(OS_MAC) + USING(OS_ANDROID) + USING(OS_GNU) == 1
);
