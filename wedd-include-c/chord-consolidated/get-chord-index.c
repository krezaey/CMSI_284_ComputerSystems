// These #include’s are just guides. Add/remove as appropriate based on your code.
#include <stdio.h>
#include <string.h>

#include "notes.h"

// ***** Copy just your `main` and program-specific helper functions here (if any). *****
int main(int argc, char** argv) {
    if (argc != 2) {
        printf("This program requires exactly one command line argument.\n");
        return 1;
    }
    if (get_chord_index(argv[1]) == INVALID) {
        printf("%s is not a valid note.\n", argv[1]);
        return 1;
    }

    printf("%s is at CHORD_SUFFIXES index %d.\n", argv[1], get_chord_index(argv[1]));
    return 0;
}
