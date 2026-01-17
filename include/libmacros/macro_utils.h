#pragma once

// Note:
// If you want to use that in a loop, please consider creating a const variable
// holding the result instead of calling that macro each time.
#define arrayCapacity(pArray) (sizeof(pArray) / sizeof(pArray[0]))
