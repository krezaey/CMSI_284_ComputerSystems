#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "io-utilities.h"
#include "mine-c-weeper.h"

void display_weeper_count(mcw_game* game, int x, int y) {
    printf("Adjacent weeper count at (%d, %d) is %d.\n", x, y, get_adjacent_weeper_count(game, x, y));
}

// Helper function for determining what kind of arguments we got.
bool file_args(int argc, char** argv) {
    return argc == 2;
}

/**
 * This program uses the Mine-C-Weeper library to test the get_adjacent_weeper_count function.
 *
 * Once you have that function working, you can integrate it into display_game_field and
 * display_game_state so that those counts show up as one would expect in the game.
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
        printf(" This tests the Mine-C-Weeper get_adjacent_weeper_count function! ");
        emit_utf_8(WEEPER);
        puts("");

        puts("Usage: test-adjacent-weeper-count <filename>");
        puts("");
        puts("Caution: File error-checking is minimal, so if the map file is in the wrong format,");
        puts("         this program may just terminate without warning.");
        return 1;
    }

    display_game_field(game);
    int x;
    int y;
    for (y = 0; y < game->height; y++) {
        for (x = 0; x < game->width; x++) {
            display_weeper_count(game, x, y);
        }
    }

    free_game(game);
    return 0;
}
