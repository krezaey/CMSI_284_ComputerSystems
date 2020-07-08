#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "io-utilities.h"
#include "mine-c-weeper.h"

void mark_count_and_display(mcw_game* game, int x, int y) {
    puts("");
    printf("Marking %d, %d...\n", x, y);
    mark_game_square(game, x, y);
    printf("Current flag count: %d\n", get_flag_count(game));
    display_game_state(game);
}

// Helper function for determining what kind of arguments we got.
bool file_args(int argc, char** argv) {
    return argc == 2;
}

/**
 * This program uses the Mine-C-Weeper library to test the display_game_state, mark_game_square,
 * and get_flag_count functions.
 *
 * Note that display_game_state might not be 100% complete yet (especially if the
 * get_adjacent_weeper_count function hasn’t been implemented), but it should be far
 * enough along to test the mark_game_square and get_flag_count functions.
 *
 * (note that this is also implicitly an additional test of the is_in_game_bounds function)
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
        printf(" This tests the Mine-C-Weeper display_game_state and mark_game_square functions! ");
        emit_utf_8(WEEPER);
        puts("");

        puts("Usage: test-mark-game-square <filename>");
        puts("");
        puts("Caution: File error-checking is minimal, so if the map file is in the wrong format,");
        puts("         this program may just terminate without warning.");
        return 1;
    }

    display_game_state(game);
    mark_count_and_display(game, 4, 3);
    mark_count_and_display(game, 1, 1);
    mark_count_and_display(game, 5, 6);
    mark_count_and_display(game, -1, 3);
    mark_count_and_display(game, 1, -1);
    mark_count_and_display(game, 10000, 3);
    mark_count_and_display(game, 1, 99999);
    mark_count_and_display(game, 4, 3);
    mark_count_and_display(game, 1, 1);

    free_game(game);
    return 0;
}
