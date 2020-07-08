#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "io-utilities.h"
#include "mine-c-weeper.h"

void reveal_and_display(mcw_game* game, int x, int y) {
    puts("");
    printf("Revealing (%d, %d)...\n", x, y);
    reveal_game_square(game, x, y);
    display_game_state(game);
}

// Helper function for determining what kind of arguments we got.
bool file_args(int argc, char** argv) {
    return argc == 2;
}

/**
 * This program uses the Mine-C-Weeper library to test the reveal_game_square function.
 *
 * This one will take multiple phases. First, start with just revealing one square. Then, if that
 * works, you will need to implement the “game-level” reveal, which opens all squares surrounding
 * the specified coordinates until you hit squares that have weepers adjacent to them.
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
        printf(" This tests the Mine-C-Weeper reveal_game_square function! ");
        emit_utf_8(WEEPER);
        puts("");

        puts("Usage: test-reveal-game-square <filename>");
        puts("");
        puts("Caution: File error-checking is minimal, so if the map file is in the wrong format,");
        puts("         this program may just terminate without warning.");
        return 1;
    }

    display_game_field(game);
    reveal_and_display(game, -3, 4);
    reveal_and_display(game, 5, -10);
    reveal_and_display(game, 4, 3);
    reveal_and_display(game, 2, 1);
    reveal_and_display(game, 2, 2);
    reveal_and_display(game, 10000, 5);
    reveal_and_display(game, 3, 29349);
    reveal_and_display(game, 1, 5);
    reveal_and_display(game, 3, 4);
    reveal_and_display(game, 4, 2);

    free_game(game);
    return 0;
}
