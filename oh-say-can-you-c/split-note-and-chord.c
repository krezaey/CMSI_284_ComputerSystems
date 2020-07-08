#include <stdio.h>
#include <string.h>

#include "notes.h"

#define MAX_SUBSTRING 15
#define INVALID -1

void split_string_at_index(char* string, int index, char* left, char* right) {
    int string_length = strlen(string);
    left[index+1];
    right[string_length-index+1];
 
    int start = 0;
    for (int k = index; k < string_length; k++) {
        right[start] = string[k];
        start++;
    }
    for (int i = 0; i < index; i++) { left[i] = string[i]; } 

    left[index] = '\0';
    right[string_length-index] = '\0';
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


// ***** IMPLEMENT ME! *****
// ***** Feel free to add more functions if you think they will make it easier to implement split_note_and_chord.
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

    printf("[%s] [%s]\n", note, chord);
    return 0;
}
