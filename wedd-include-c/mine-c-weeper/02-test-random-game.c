#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "io-utilities.h"
#include "string-plus.h"
#include "mine-c-weeper.h"

// Helper function for determining what kind of arguments we got.
bool dimension_and_probability_args(int argc, char** argv) {
    return argc == 4 && is_non_negative_numeral(argv[1]) && is_non_negative_numeral(argv[2]) &&
        is_non_negative_numeral(argv[3]);
}

/**
 * This program uses the Mine-C-Weeper library to create and display a random mine-c-weeper game field,
 * given a width, a height, and a percentage probability.
 *
 * (what this program _really_ is is a test of the alloc_game, free_game, and display_game_field functions)
 */
int main(int argc, char** argv) {
    mcw_game* game;

    // Check arguments to figure out if we can initialize the game.
    if (dimension_and_probability_args(argc, argv)) {
        // We already checked for numerals so we can convert right away.
        int width = atoi(argv[1]);
        int height = atoi(argv[2]);
        int probability = atoi(argv[3]);

        if (width < 1 || height < 1) {
            puts("Sorry, but zero dimensions are not allowed.");
            return 1;
        }

        // Don’t worry about the srandom() call---but don’t change or remove it either!
        // It’s related to random number generation.
        srandom(time(NULL));
        game = initialize_random_game(width, height, probability);
        if (game == NULL) {
            puts("Sorry, but something went wrong with random game generation.");
            return 1;
        }
    } else {
        emit_utf_8(MARKER);
        printf(" This is a random Mine-C-Weeper field creator! ");
        emit_utf_8(WEEPER);
        puts("");

        puts("Usage: test-random-game <width> <height> <weeper frequency>");
        puts("");
        puts("The weeper frequency is the chance that a given square is a weeper: this should be an integer");
        puts("from 0 to 100.");
        return 1;
    }

    display_game_field(game);
    free_game(game);
    return 0;
}
