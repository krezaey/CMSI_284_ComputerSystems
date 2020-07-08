#ifndef _NOTES_H
#define _NOTES_H

#define INVALID -1

// These definitions now reside in notes.c for proper shared-code compilation.
extern char* NOTES[];
extern int NOTE_COUNT;
extern char* CHORD_SUFFIXES[];
extern int CHORD_COUNT;
extern int CHORD_STEPS[][3];
extern int CHORD_STEP_COUNT[];

/**
 * This function returns the length of the longest string in the `NOTES` string array.
 */
int get_max_note_length();

/**
 * This function returns the length of the longest string in the `CHORD_SUFFIXES` string array.
 */
int get_max_chord_suffix_length();

/**
 * Given a C string, this function returns the zero-based index of the `NOTES` array in
 * which that string appears. It returns -1 if said string is not in that array.
 *
 * For convenience, an INVALID symbol is defined as -1 in this .h file.
 */
int get_note_index(char* string);

/**
 * Given a C string, this function returns the zero-based index of the `CHORD_SUFFIXES`
 * array in which that string appears. It returns -1 if said string is not in that array.
 *
 * For convenience, an INVALID symbol is defined as -1 in this .h file.
 */
int get_chord_index(char* string);

/**
 * This function takes the string given as its first argument, identifies where the note ends
 * and the chord suffix starts, then copies just the note part into the note argument and the
 * chord suffix part into the chord argument, returning `0` to indicate a successful split.
 * If the string argument does not express a valid chord (e.g., `X7` or `Gblarg`), the
 * function puts empty strings in `note` and `chord` then returns `-1` as its result.
 *
 * For convenience, an INVALID symbol is defined as -1 in this .h file.
 */
int split_note_and_chord(char* string, char* note, char* chord);

/**
 * This function accepts two command line arguments, one for an index in the `NOTES` array
 * and another for an index in the `CHORD_STEPS` array. Given those indices, it prints
 * (a) the chord that they represent then (b) the notes in that chord, in the following
 * format (e.g., for DM7):
 *
 * DM7: D Gb A Db
 */
void print_chord(int note_index, int chord_index);

#endif
