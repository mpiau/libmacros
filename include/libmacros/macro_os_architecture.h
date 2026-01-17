#pragma once

#include "macro_conditional_compilation.h"


//================================================================================================
// Operating System (OS) Architecture Identification
//================================================================================================

#if   defined __LP64__   || defined _LP64    || defined __amd64__   || defined __amd64 \
   || defined __x86_64__ || defined __x86_64 || defined __aarch64__ || defined _WIN64
#  define OS_ARCH_64_BITS   IN_USE
#  define OS_ARCH_32_BITS   NOT_IN_USE

#elif defined i386 || defined __i386 || defined __i386__ || defined _M_I86
#  define OS_ARCH_64_BITS   NOT_IN_USE
#  define OS_ARCH_32_BITS   IN_USE

#else
#  error Impossible to determine the current OS Architecture (32/64 bits).

#endif


//------------------------------------------------------------------------------------------------

// Ensures that only one of the macros is defined as IN_USE.
static_assert(USING(OS_ARCH_64_BITS) + USING(OS_ARCH_32_BITS) == 1);
