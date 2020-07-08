#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "io-utilities.h"
#include "mine-c-weeper.h"

void check_for_win(mcw_game* game) {
    display_game_state(game);
    if (is_game_over_win(game)) {
        puts("The player has won!");
    } else {
        puts("The player has not won!");
    }
}

void reveal_and_check(mcw_game* game, int x, int y) {
    puts("");
    printf("Revealing (%d, %d)...\n", x, y);
    reveal_game_square(game, x, y);
    check_for_win(game);
}

void mark_and_check(mcw_game* game, int x, int y) {
    puts("");
    printf("Marking (%d, %d)...\n", x, y);
    mark_game_square(game, x, y);
    check_for_win(game);
}

// Helper function for determining what kind of arguments we got.
bool file_args(int argc, char** argv) {
    return argc == 2;
}

/**
 * This program uses the Mine-C-Weeper library to test the is_game_over_win function.
 *
 * At this point, reveal_game_square and mark_game_square should be working correctly;
 * otherwise we wouldn’t reach the right win condition!
 *
 * Note that this test is written primarily against the provided test.mcw file because
 * getting to the loss condition requires some specific knowledge of the field. If you
 * use a different file, results will of course vary (unless you change the moves too).
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
        printf(" This tests the Mine-C-Weeper is_game_over_win function! ");
        emit_utf_8(WEEPER);
        puts("");

        puts("Usage: test-is-game-over-win <filename>");
        puts("");
        puts("Caution: File error-checking is minimal, so if the map file is in the wrong format,");
        puts("         this program may just terminate without warning.");
        return 1;
    }

    display_game_field(game);
    reveal_and_check(game, -3, 4);
    reveal_and_check(game, 5, -10);
    reveal_and_check(game, 4, 3);
    reveal_and_check(game, 1, 5);
    reveal_and_check(game, 10000, 5);
    reveal_and_check(game, 3, 29349);
    reveal_and_check(game, 3, 4);
    mark_and_check(game, 0, 6);
    reveal_and_check(game, 4, 2);
    mark_and_check(game, 2, 2);
    mark_and_check(game, 2, 1);
    mark_and_check(game, 4, 6);
    mark_and_check(game, 5, 4);
    reveal_and_check(game, 2, 0);
    reveal_and_check(game, 3, 0);
    reveal_and_check(game, 5, 5);
    reveal_and_check(game, 5, 6);
    mark_and_check(game, 4, 0);
    reveal_and_check(game, 6, 0);
    reveal_and_check(game, 6, 6);
    mark_and_check(game, 6, 2);
    mark_and_check(game, 6, 2);
    mark_and_check(game, 2, 1);
    mark_and_check(game, 6, 2);
    mark_and_check(game, 2, 1);

    free_game(game);
    return 0;
}
