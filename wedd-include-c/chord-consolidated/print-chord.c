// These #include’s are just guides. Add/remove as appropriate based on your code.
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "string-plus.h"
#include "notes.h"

// ***** Copy just your `main` and program-specific helper functions here (if any). *****
int main(int argc, char** argv) {
    if (argc != 3) {
        printf("This program requires exactly two command line arguments:\n");
        printf("The NOTES index and the CHORD_SUFFIXES index of the note and chord suffix to print, respetively.\n");
        return 1;
    }
    if (!is_non_negative_numeral(argv[1]) || !is_non_negative_numeral(argv[2])) {
        printf("Either %s or %s is not a valid index.\n", argv[1], argv[2]);
        return 1;
    }
    
    int notes_index = atoi(argv[1]);
    int chords_index = atoi(argv[2]);

    if (notes_index < 0 || notes_index > NOTE_COUNT-1 || chords_index < 0 || chords_index > CHORD_COUNT-1) {
        printf("Either %d or %d is out of range.\n", notes_index, chords_index);
        return 1;
    } 

    print_chord(notes_index, chords_index);
    return 0;
}
