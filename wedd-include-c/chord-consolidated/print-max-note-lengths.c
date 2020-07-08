// These #include’s are just guides. Add/remove as appropriate based on your code.
#include <stdio.h>
#include <string.h>

#include "notes.h"

// ***** Copy just your `main` and program-specific helper functions here (if any). *****
int main(int argc, char** argv) {
    if (argc != 1) {
        printf("This program does not expect any command line arguments.\n");
        return 1;
    }
    printf("The longest NOTES string is %d characters long and the longest CHORD_SUFFIXES string is %d characters long.\n",  get_max_note_length(), get_max_chord_suffix_length());
    return 0;
}
