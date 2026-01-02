//================================================================================================
// THIS FILE HAS BEEN GENERATED. PLEASE DO NOT MANUALLY MODIFY
// -----------------------------------------------------------
// Script used:   ./generator.out
// Configuration: test.enum
//================================================================================================

#include <stdint.h>
#include <stdio.h>


enum WindDirection : uint8_t
{
     WindDirection_NORTH = 0
   , WindDirection_SOUTH
   , WindDirection_EAST
   , WindDirection_WEST
};
typedef enum WindDirection WindDirection;


// Returns the number of members in the enum
[[nodiscard]] inline uint8_t wind_direction_count(void)
{
   return 4;
}

