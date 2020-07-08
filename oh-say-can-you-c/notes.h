#ifndef __NOTES_DEFINITIONS__
#define __NOTES_DEFINITIONS__

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

char *INTERVALS[] = {
  "perfect octave", "minor second", "major second", "minor third", "major third",
  "perfect fourth", "tritone", "perfect fifth", "minor sixth", "major sixth",
  "minor seventh", "major seventh"
};

#endif
