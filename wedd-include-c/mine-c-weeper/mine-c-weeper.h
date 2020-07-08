#ifndef _MINE_C_WEEPER_H
#define _MINE_C_WEEPER_H

#include <stdbool.h>

// We intentionally choose names that are distinct from the character names
// to emphasize their meaning in the _game_ and not as characters.
#define HIDDEN 0x1F535
#define WEEPER 0x1F602
#define MARKER 0x1F6A9

typedef enum {
    open=0,
    weeper=1
} mcw_square;

typedef enum {
    hidden=0,
    revealed=1,
    flagged=2
} mcw_status;

typedef struct {
    int width;
    int height;
    mcw_square** field;
    mcw_status** status;
} mcw_game;

/**
 * Frees up the memory occupied by the game.
 * This function can’t tell if a game has been validly initialized, so _don’t_ use it on such a game.
 * Unpredictable results ensue if this is done.
 *
 * After this function is called, the game is no longer usable.
 */
void free_game(mcw_game* game);

/**
 * Initializes a game at random, with the indicated dimensions and (integer) probability that a square
 * has a mine. The probability is interpreted as a percent chance: e.g., probabiliy == 35 represents
 * a 35% chance that a square will be a mine.
 *
 * Probabilities greater than 100 are clamped at 100. Of course, you’ll want the probability to be
 * much lower than that to make the game anywhere near playable!
 */
mcw_game* initialize_random_game(int width, int height, int probability);

/**
 * Initializes a game from the given file. The file format is as follows:
 * - The first line contains the width and the height of the field, separated by a space, e.g.:
 *
 *   20 20
 *
 * - All other lines consist of a row containing <width> characters
 * - There should be <height> lines in all (after the first line with the dimensions)
 * - For each row line, use a period (.) to represent an empty square and a capital W
 *   to represent a weeper, e.g.:
 *
 *   ....W.......W.....WW
 *
 * Error-checking is minimal—if there’s something wrong with the file format, the function will
 * either terminate unexpectedly or return NULL.
 */
mcw_game* initialize_file_game(char* filename);

// **IMPORTANT IMPLEMENTATION NOTE**
//
// For all functions that operate on an existing game, the game is assumed to be valid.
// (i.e., correctly allocated and initialized according to its width and height fields)
//
// If a function terminates unexpectedly, make sure to differentiate between a termination
// because the game was improperly initialized vs. because the function is buggy.
//
// **END OF IMPORTANT IMPLEMENTATION NOTE**

/**
 * Prints the entire game field, independent of each square’s status, to the terminal.
 * Used primarily for testing---not really part of the game. One can think of it as a
 * “god mode” display so that you can peek into the board without having to reveal any
 * squares first.
 */
void display_game_field(mcw_game* game);

/**
 * Marks all squares as revealed: typically used when the game ends to reveal the entire field to the player.
 */
void show_all(mcw_game* game);

/**
 * Returns the number of weepers in an initialized game.
 */
int get_weeper_count(mcw_game* game);

/**
 * Returns the number of flags in an initialized (possibly on-going) game.
 */
int get_flag_count(mcw_game* game);

/**
 * The heart of the game: returns the number of weepers that are adjacent to the given square.
 */
int get_adjacent_weeper_count(mcw_game* game, int x, int y);

/**
 * Prints the game state, factoring each square’s status.
 */
void display_game_state(mcw_game* game);

/**
 * Returns whether the given coordinates are in the game’s coordinate range.
 */
bool is_in_game_bounds(mcw_game* game, int x, int y);

/**
 * Toggles a flag/mark on the given coordinates. A hidden square becomes flagged, a flagged square becomes hidden.
 *
 * If the x or y coordinates are out of range, nothing happens.
 */
void mark_game_square(mcw_game* game, int x, int y);

/**
 * Unhides a game square and its applicable neighboring squares until a squares that are adjacent to mines
 * are discovered.
 *
 * If the chosen square is no longer hidden or the x or y coordinates are out of range, nothing happens.
 */
void reveal_game_square(mcw_game* game, int x, int y);

/**
 * Returns whether a game has been lost: i.e., there is a revealed square with a weeper under it.
 */
bool is_game_over_loss(mcw_game* game);

/**
 * Returns whether a game is won: i.e., every flagged square has a weeper under it,
 * and every other square is revealed.
 */
bool is_game_over_win(mcw_game* game);

#endif
