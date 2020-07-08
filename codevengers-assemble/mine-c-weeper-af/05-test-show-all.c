#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "io-utilities.h"
#include "mine-c-weeper.h"

// Helper function for determining what kind of arguments we got.
bool file_args(int argc, char** argv) {
    return argc == 2;
}

/**
 * This program uses the Mine-C-Weeper library to test the display_game_state and show_all
 * functions. Note that display_game_state might not be 100% complete yet (especially if the
 * get_adjacent_weeper_count function hasn’t been implemented), but it should be enough to test
 * the show_all function.
 */
int main(int argc, char** argv) {
    mcw_game* game;

    // Check arguments to figure out if we can initialize the game.
    if (file_args(argc, argv)) {
        game = initialize_file_game(argv[1]);
        if (game == NULL) {
            puts("Sorry, but something appears to be amiss with the game file.");
            return 1;
        }
    } else {
        emit_utf_8(MARKER);
        printf(" This tests the Mine-C-Weeper display_game_state and show_all functions! ");
        emit_utf_8(WEEPER);
        puts("");

        puts("Usage: test-show-all <filename>");
        puts("");
        puts("Caution: File error-checking is minimal, so if the map file is in the wrong format,");
        puts("         this program may just terminate without warning.");
        return 1;
    }

    puts("Before show_all...");
    display_game_state(game);

    show_all(game);
    puts("\nAfter show_all...");
    display_game_state(game);

    free_game(game);
    return 0;
}
