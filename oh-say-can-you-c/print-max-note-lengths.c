#include <stdio.h>
#include <string.h>

#include "notes.h"

// ***** IMPLEMENT ME! *****
int get_max_note_length() {
    int max_length = 0; 
    int new_length = 0;
    for (int i = 0; i < NOTE_COUNT; i++) {
        new_length = strlen(NOTES[i]);
        if (new_length > max_length) { max_length = new_length; }
    }
    return max_length;
}

// ***** IMPLEMENT ME! *****
int get_max_chord_suffix_length() {
    int max_length = 0; 
    int new_length = 0;
     for (int i = 0; i < CHORD_COUNT; i++) {
         new_length = strlen(CHORD_SUFFIXES[i]);
        if (new_length > max_length) { max_length = new_length; }
    }
    return max_length;
}

int main(int argc, char** argv) {
    if (argc != 1) {
        printf("This program does not expect any command line arguments.\n");
        return 1;
    }
    printf("The longest NOTES string is %d characters long and the longest CHORD_SUFFIXES string is %d characters long.\n",  get_max_note_length(), get_max_chord_suffix_length());
    return 0;
}
