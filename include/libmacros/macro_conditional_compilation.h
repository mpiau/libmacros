#pragma once

// Example of usage:
// -----------------
//
// #define SYSTEMS    IN_USE
// #define SYSTEM_X   USING(SYSTEMS) && USING([...])
// #define SYSTEM_Y   USING(SYSTEMS) && USING(SYSTEM_X)
// #define SYSTEM_Z   USING(SYSTEMS) && !USING(SYSTEM_X)
//
// #if USING(SYSTEM_Z)
// [...]
// #endif
//

//================================================================================================
// Conditional Compilation
//================================================================================================

// The goal of these defines is to provide an uniform way of declaring conditional-compilation
// components across the project. It also prevents the mistake of checking if the value is
// defined instead of being true/false.

#if defined IN_USE || defined NOT_IN_USE || defined USING
   #error IN_USE / NOT_IN_USE / USING already defined somewhere else !
#endif

#define IN_USE       1
#define NOT_IN_USE   0

#define USING(cond)  (cond == 1)
