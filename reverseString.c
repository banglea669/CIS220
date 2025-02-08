// Austin Bangle
// Chpt2 PA

#include <stdio.h>
#include <string.h>

// Function to recursively reverse a string
char* ReverseString(char* stringToReverse) {
    static char reversedStr[21];  // Static array to hold the reversed string
    static int index = 0;         // Index to track position in reversed string
    
    // Base case: If the string is empty, return
    if (*stringToReverse == '\0') {
        reversedStr[index] = '\0'; // Null terminate the reversed string
        return reversedStr;
    }
    
    // Recursive case: Call function with the next character
    ReverseString(stringToReverse + 1);
    
    // Append current character to the reversed string
    reversedStr[index++] = *stringToReverse;
    
    return reversedStr;
}

int main(void) {
    char inStr[21]; // Maximum input length is 20 characters + null terminator
    char* resultStr;
   
    printf("Enter the string to be reversed: ");
    fgets(inStr, 20, stdin);
    strtok(inStr, "\n");  // Remove newline character from input
    
    // Reset static variables before each function call
    resultStr = ReverseString(inStr);
    
    printf("Reversed: %s\n", resultStr);

    return 0;
}