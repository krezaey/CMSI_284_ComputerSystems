// These #include’s are just guides. Add/remove as appropriate based on your code.
#include <stdio.h>
#include <string.h>

#include "string-plus.h"
#include "notes.h"

#define MAX_SUBSTRING 15

// ***** Copy just your `main` and program-specific helper functions here (if any). *****
int main(int argc, char** argv) {
    if (argc != 2) {
        printf("This program requires exactly one command line argument.\n");
        return 1;
    }

    char* string_to_split = argv[1];
    char note[MAX_SUBSTRING+1];
    char chord[MAX_SUBSTRING+1];
    split_note_and_chord(string_to_split, note, chord);
    
    if (split_note_and_chord(string_to_split, note, chord) == INVALID || strlen(argv[1]) > MAX_SUBSTRING) {
        printf("%s is not a valid chord.\n", argv[1]);
        return 1;
    }

    int note_index = get_note_index(note);
    int chord_index = get_chord_index(chord);
    print_chord(note_index, chord_index);
    return 0;
}
