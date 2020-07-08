#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "io-utilities.h"
#include "string-plus.h"
#include "mine-c-weeper.h"

#define DEFAULT_PROBABILITY 10

void display_bounds(mcw_game* game, int x, int y) {
    printf("(%d, %d) is%s out of bounds.\n", x, y, is_in_game_bounds(game, x, y) ? " not" : "");
}

// Helper function for determining what kind of arguments we got.
bool dimension_args(int argc, char** argv) {
    return argc == 3 && is_non_negative_numeral(argv[1]) && is_non_negative_numeral(argv[2]);
}

/**
 * This program uses the Mine-C-Weeper library to test the is_in_game_bounds function.
 * If you know the dimensions of the game that you created, there’s really no need to
 * display anything, so we’ll keep it simple like that.
 */
int main(int argc, char** argv) {
    mcw_game* game;

    // Check arguments to figure out if we can initialize the game.
    if (dimension_args(argc, argv)) {
        // We already checked for numerals so we can convert right away.
        int width = atoi(argv[1]);
        int height = atoi(argv[2]);

        if (width < 1 || height < 1) {
            puts("Sorry, but zero dimensions are not allowed.");
            return 1;
        }

        // Don’t worry about the srandom() call---but don’t change or remove it either!
        // It’s related to random number generation.
        srandom(time(NULL));
        game = initialize_random_game(width, height, DEFAULT_PROBABILITY);
        if (game == NULL) {
            puts("Sorry, but something went wrong with random game generation.");
            return 1;
        }
    } else {
        emit_utf_8(MARKER);
        printf(" This tests the Mine-C-Weeper is_in_game_bounds function! ");
        emit_utf_8(WEEPER);
        puts("");

        puts("Usage: test-is-in-game-bounds <width> <height>");
        puts("");
        puts("The weeper frequency does not matter for this test so we give it a default.");
        return 1;
    }

    display_game_field(game);
    display_bounds(game, 0, 0);
    display_bounds(game, -10, 0);
    display_bounds(game, 0, -4);
    display_bounds(game, 3, 4);
    display_bounds(game, 6, 7);
    display_bounds(game, 7, 6);
    display_bounds(game, 19, 13);
    display_bounds(game, 1000, 0);
    display_bounds(game, 0, 1000);
    display_bounds(game, 10000, 24000);

    free_game(game);
    return 0;
}
