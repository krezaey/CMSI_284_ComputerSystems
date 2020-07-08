#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "string-plus.h"
#include "notes.h"

#define MAX_SUBSTRING 15

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
