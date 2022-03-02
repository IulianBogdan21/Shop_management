// This file contains utils functions used in the program

#ifndef UTILS_H_
#define UTILS_H_

#include "constants.h"


/// Removes all spaces from the begining and the end of the Cstring
/// Pre: string_pointer- pointer to a Cstring
/// Post: all spaces from the begining and the end will be removed
void stripSpacesFromString(char* string_pointer);

/// Checks if the given Cstring can be converted to int
/// Pre: string_pointer- pointer to a Cstring with no trailing spaces
/// Returns TRUE if the string can be converted to int, FALSE otherwise
int isStringInteger(char* string_pointer);

/// Checks if the given Cstring can be converted to float
/// Pre: string_pointer- pointer to a Cstring with no trailing spaces
/// Returns TRUE if the string can be converted to float, FALSE otherwise
int isStringFloat(char* string_pointer);

#endif // !UITILS_H_

