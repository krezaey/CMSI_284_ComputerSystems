#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "notes.h"

#define INVALID -1

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
void print_chord(int note_index, int chord_index) {
    int chord_count = CHORD_STEP_COUNT[chord_index];
    char final_result[100];
    strcpy(final_result, NOTES[note_index]);
    char* empty_space = " ";
    char* to_add;

    int track_index = note_index;
    for (int i = 0; i < chord_count; i++) {
        if (track_index + CHORD_STEPS[chord_index][i] > NOTE_COUNT - 1) {
            track_index = track_index + CHORD_STEPS[chord_index][i] - NOTE_COUNT;
        }
        else { track_index = track_index + CHORD_STEPS[chord_index][i]; }
        strcpy(to_add, NOTES[track_index]);
        strcat(final_result, empty_space);
        strcat(final_result, to_add);
    }
   printf("%s%s: %s\n", NOTES[note_index], CHORD_SUFFIXES[chord_index], final_result);
}

// ***** Feel free to add more functions if you think they will make it easier to check argument validity.
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
