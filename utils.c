#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include "constants.h"

void stripSpacesFromString(char* string_pointer)
{
    while (strlen(string_pointer) > 0 && *string_pointer == ' ')
        strcpy_s(string_pointer, strlen(string_pointer), string_pointer + 1);
    
    if (strlen(string_pointer) == 0)
        return;

    char* pointerToLastCharacter = string_pointer + strlen(string_pointer) - 1;

    while (*pointerToLastCharacter == ' ')
        pointerToLastCharacter--;

    while(strlen(pointerToLastCharacter) > 1)
        strcpy_s(pointerToLastCharacter +1, strlen(pointerToLastCharacter), pointerToLastCharacter + 2);
    return;
}


int isStringInteger(char* string_pointer)
{
    if (strlen(string_pointer) == 0)
        return FALSE;

    if (*string_pointer == '-' || ('0' <= *string_pointer && *string_pointer <= '9'))
        string_pointer++;
    
    while (strlen(string_pointer) > 0)
    {
        if ('0' > *string_pointer || *string_pointer > '9')
            return FALSE;
        string_pointer++;
    }
    
    return TRUE;
}

int isStringFloat(char* string_pointer)
{
    char* pointerToFloatingPoint = strchr(string_pointer, '.');

    if (pointerToFloatingPoint == NULL)
        return isStringInteger(string_pointer);
    else 
    {
        if (string_pointer == pointerToFloatingPoint || string_pointer + strlen(string_pointer) - 1 == pointerToFloatingPoint)
            return FALSE;

        if (*(pointerToFloatingPoint + 1) == '-')
            return FALSE;

        char charsBeforeFloatingPoint[MAX_STRING_SIZE];
        strncpy_s(charsBeforeFloatingPoint, MAX_STRING_SIZE, string_pointer, pointerToFloatingPoint - string_pointer);

        char charsAfterFloatingPoint[MAX_STRING_SIZE];
        strncpy_s(charsAfterFloatingPoint, MAX_STRING_SIZE, pointerToFloatingPoint+1, strlen(pointerToFloatingPoint) -1);

        return (isStringInteger(charsBeforeFloatingPoint) &&
            isStringInteger(charsAfterFloatingPoint)) == TRUE;
    }
}
