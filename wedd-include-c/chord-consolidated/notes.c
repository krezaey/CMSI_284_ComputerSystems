#include <stdbool.h>
#include <stdio.h>
#include <string.h>  // In case your implementation needs it. It does not have to.

#include "string-plus.h"
#include "notes.h"

#define MAX_SUBSTRING 15

char *NOTES[] = {"A", "Bb", "B", "C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab"};
int NOTE_COUNT = sizeof(NOTES) / sizeof(char*);

// C has more sophisticated ways to express these structures, but at our level we
// stay with multiple arrays that have coordinated index values (i.e., the same
// index on these arrays corresopnds to the same type of chord).
char *CHORD_SUFFIXES[] = {
    "",     // major
    "m",    // minor
    "7",    // dominant 7th
    "M7",   // major 7th
    "m7",   // minor 7th
    "dim7"  // diminished 7th
};

int CHORD_COUNT = sizeof(CHORD_SUFFIXES) / sizeof(char*);

// C needs to know the maximum size of the inner array, but not the outer one 🤷🏽‍♂️
int CHORD_STEPS[][3] = {
    {4, 3},     // major
    {3, 4},     // minor
    {4, 3, 3},  // dominant 7th
    {4, 3, 4},  // major 7th
    {3, 4, 3},  // minor 7th
    {3, 3, 3}   // diminished 7th
};

// Yes, there are ways of computing this dynamically but for now we choose to list
// them explicitly to show how these arrays correspond to each other.
int CHORD_STEP_COUNT[] = {
    2,  // major
    2,  // minor
    3,  // dominant 7th
    3,  // major 7th
    3,  // minor 7th
    3   // diminished 7th
};

// ***** MOVE YOUR IMPLEMENTATIONS HERE! *****
int get_max_note_length() {
    int max_length = 0; 
    int new_length = 0;
    for (int i = 0; i < NOTE_COUNT; i++) {
        new_length = strlen(NOTES[i]);
        if (new_length > max_length) { max_length = new_length; }
    }
    return max_length;
}

int get_max_chord_suffix_length() {
    int max_length = 0; 
    int new_length = 0;
     for (int i = 0; i < CHORD_COUNT; i++) {
         new_length = strlen(CHORD_SUFFIXES[i]);
        if (new_length > max_length) { max_length = new_length; }
    }
    return max_length;
}

int get_note_index(char* string) {
    for (int i = 0; i < NOTE_COUNT; i++) {
        if (strcmp(string, NOTES[i]) == 0) { return i; }
    }
    return INVALID;
}

int get_chord_index(char* string) {
     for (int i = 0; i < CHORD_COUNT; i++) {
        if (strcmp(string, CHORD_SUFFIXES[i]) == 0) { return i; }
    }
    return INVALID;
}

int find_note_length(char* string, char* note) {
    int note_length = 0;
    char possible_note[3];
    for (int i = 0; i < 2; i++) { possible_note[i] = string[i]; }
    possible_note[2] = '\0';
    note_length = 2;
    if (get_note_index(possible_note) == INVALID) { note_length = 1; }
    return note_length;
}

int split_note_and_chord(char* string, char* note, char* chord) {
    int note_length = find_note_length(string, note);
    char final_note[note_length+1];
    char final_chord[strlen(string)-note_length+1];

    split_string_at_index(string, note_length, final_note, final_chord);
    strcpy(note, final_note);
    strcpy(chord, final_chord);
    if (strcmp(note, chord) == 0) { chord[0] = '\0'; }
    
    if (get_note_index(note) == INVALID || get_chord_index(chord) == INVALID) { return INVALID; }
    return 0;
}

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
