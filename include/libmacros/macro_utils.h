#pragma once

// While sizeof() retrieves the size in bytes of the given type,
// sizeofArrayElem() retrieves the size of one element within a static array.
// Note:
// If you want to use that in a loop, please consider creating a const variable
// holding the result instead of calling that macro each time.
#define sizeofArrayElem(pArray) (sizeof(pArray) / sizeof(pArray[0]))
