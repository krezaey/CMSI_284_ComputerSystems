#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// ***** IMPLEMENT ME! *****
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

int main(int argc, char** argv) {
    // Check for the correct number of arguments.
    if (argc != 3) {
        printf("This program requires exactly two command line arguments:\n");
        printf("The string to split and the index at which to split it.\n");
        return 1;
    }

    char* string_to_split = argv[1];
    char* index_string = argv[2];

    // Check that the second argument is in the correct format.
    if (!is_non_negative_numeral(index_string)) {
        printf("%s is not a valid index.\n", index_string);
        return 1;
    }

    char left[MAX_SUBSTRING + 1];
    char right[MAX_SUBSTRING + 1];

    int string_length = strlen(string_to_split);
    int index = atoi(index_string);

    // Check that the given index is within the correct range (two conditions for this---hope you can see why).
    if (index < 0 || index > string_length) {
        printf("The index %d out of range.\n", index);
        return 1;
    }

    if (index > MAX_SUBSTRING || string_length - index > MAX_SUBSTRING) {
        printf("Splitting at %d will exceed the limit of %d characters per substring.\n", index, MAX_SUBSTRING);
        return 1;
    }

    // Now that we have validated the user’s input, we can call the function.
    split_string_at_index(string_to_split, index, left, right);
    printf("[%s] [%s]\n", left, right);
    return 0;
}
