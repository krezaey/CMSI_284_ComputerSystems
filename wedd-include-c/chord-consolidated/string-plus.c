#include <stdbool.h>
#include <string.h>  // In case your implementation needs it. It does not have to.

#define MAX_SUBSTRING 15

// Helper function for determining if a string validly expresses a non-negative integer.
// Feel free to use where needed (and to study it as an example).
bool is_non_negative_numeral(char* numeral) {
    int numeral_length = strlen(numeral);
    for (int i = 0; i < numeral_length; i++) {
        if (numeral[i] < '0' || numeral[i] > '9') {
            return false;
        }
    }

    return true;
}

// ***** MOVE YOUR IMPLEMENTATION HERE! *****
void split_string_at_index(char* string, int index, char* left, char* right) {
    int string_length = strlen(string);
    left[index+1];
    right[string_length-index+1];
 
    int start = 0;
    for (int k = index; k < string_length; k++) {
        right[start] = string[k];
        start++;
    }
    for (int i = 0; i < index; i++) { left[i] = string[i];} 

    left[index] = '\0';
    right[string_length-index] = '\0';
}
