#include <stdio.h>
#include <stdlib.h>

#include "io-utilities.h"
#include "mine-c-weeper.h"

#define BUFFER_SIZE 1024
#define MAX_PROBABILITY 100

#define OPEN_CHAR '.'
#define WEEPER_CHAR 'W'

// ***** IMPLEMENT ME! *****
/**
 * Allocates the memory required for a game with the given dimensions, and sets those dimensions
 * in the resulting game structures `width` and `height` fields.
 *
 * In particular, sufficient memory should be allocated for:
 * - The `mcw_game` structure
 * - The two-dimensional `field` array of square contents (`open` or `weeper`)
 * - The two-dimensional `status` array reflecting the player’s progress
 *   (squares start out `hidden` then are either `revealed` or `flagged` as the game progresses)
 *
 * This function is given enough information to allocate memory _precisely_—no more and no less
 * than required. The implementation must reflect this precision.
 *
 * This function is only supposed to _allocate_ memory for the game, not initialize its squares.
 * Aside from memory, the only other values that this function should set are the `width` and
 * `height` of the game, as indicated by the function arguments.
 *
 * Excessively large hard-coded memory allocations will incur large deductions even if they
 * produce a functional game.
 *
 * You can use the given `initialize_random_game` and `initialize_file_game` functions as
 * references for how a correctly-allocated game structure and arrays will be used.
 */
mcw_game* alloc_game(int width, int height) {
    mcw_game* game = malloc(sizeof(mcw_game));
    game->width = width;
    game->height = height;
    game->field = malloc(height * sizeof(mcw_square*));
    game->status = malloc(height * sizeof(mcw_square*));

    for (int i = 0; i < height; i++) {
        game->field[i] = malloc(width * sizeof(mcw_square*));
        game->status[i] = malloc(width * sizeof(mcw_square*));
    }

    return game;
}

// ***** IMPLEMENT ME! *****
void free_game(mcw_game* game) {
    for (int i = 0; i < game->height; i++) {
        free(game->field[i]);
        free(game->status[i]);
    }

    free(game->field);
    free(game->status);
    free(game);
}

void game_setter(mcw_game* game, int set) {
    for (int i = 0; i < game->height; i++) {
        for (int j = 0; j < game->width; j++) {
            game->status[i][j] = set;
        }
    }
}
// ***** IMPLEMENT ME! *****
void show_all(mcw_game* game) {
    game_setter(game, revealed);
}

// ***** IMPLEMENT ME! *****
// This isn’t a “public” function but is used by the initialize functions.
// If you can implement `show_all`, then `hide_all` won’t be that far behind.
// You can even write a helper function (hint hint) that would make these functions
// one-liners.
void hide_all(mcw_game* game) {
    game_setter(game, hidden);
}

// The initialization functions have been written for you, but note they will not work
// until `alloc_game` has been implemented.
mcw_game* initialize_random_game(int width, int height, int probability) {
    mcw_game* game = alloc_game(width, height);
    if (game == NULL) {
        return NULL;
    }

    int threshold = probability > MAX_PROBABILITY ? MAX_PROBABILITY : probability;

    int x, y;
    for (y = 0; y < game->height; y++) {
        for (x = 0; x < game->width; x++) {
            int mine_roll = random() % MAX_PROBABILITY;
            game->field[y][x] = mine_roll < threshold ? weeper : open;
        }
    }

    hide_all(game);
    return game;
}

mcw_game* initialize_file_game(char* filename) {
    FILE* game_file = fopen(filename, "r");
    if (!game_file) {
        return NULL;
    }

    char buffer[BUFFER_SIZE];
    mcw_game* game = NULL;
    int y = 0;
    while (!feof(game_file)) {
        fgets(buffer, BUFFER_SIZE, game_file);
        if (game == NULL) {
            int width;
            int height;
            int successful_scans = sscanf(buffer, "%d %d", &width, &height);
            if (successful_scans < 2) {
                fclose(game_file);
                return NULL;
            } else {
                game = alloc_game(width, height);
                if (game == NULL) {
                    fclose(game_file);
                    return NULL;
                }
            }
        } else {
            if (y >= game->height) {
                break;
            }

            int x;
            for (x = 0; x < game->width; x++) {
                if (buffer[x] == OPEN_CHAR || buffer[x] == WEEPER_CHAR) {
                    game->field[y][x] = buffer[x] == OPEN_CHAR ? open : weeper;
                } else {
                    fclose(game_file);
                    return NULL;
                }
            }

            y++;
        }
    }

    fclose(game_file);
    return game;
}

// Don’t hesitate to write helper functions for yourself when implementing the “public” functions.
// They will reduce code duplication and, with good names, they will make your code more readable.

// ***** IMPLEMENT ME! *****
void display_game_field(mcw_game* game) {
    printf("  ");
    for (int i = 0; i < game->width; i++) {
        printf("%2d", i);
    }
    puts("");
    for (int y = 0; y < game->height; y++) {
        printf("%2d", y);
        for (int x = 0; x < game->width; x++) {
            if (game->field[y][x] == weeper) {
                emit_utf_8(WEEPER);
            }
            if (game->field[y][x] == open) {
                printf("%2d", get_adjacent_weeper_count(game, x, y));
            }   
        }
        puts("");
    }   
}

// ***** IMPLEMENT ME! *****
int get_weeper_count(mcw_game* game) {
    int count = 0;
    for (int i = 0; i < game->height; i++) {
        for (int j = 0; j < game->width; j++) {
            if (game->field[i][j] == weeper) { count++; }
        }
    }
    return count;
}

// ***** IMPLEMENT ME! *****
int get_flag_count(mcw_game* game) {
    int count = 0;
    for (int i = 0; i < game->height; i++) {
        for (int j = 0; j < game->width; j++) {
            if (game->status[i][j] == flagged) { count++; }
        }
    }
    return count;
}


// ***** IMPLEMENT ME! *****
int get_adjacent_weeper_count(mcw_game* game, int x, int y) {
    int count = 0;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (is_in_game_bounds(game, x+i, y+j)) {
                if (game->field[y+j][x+i] == weeper) {
                    count++;
                }
            }
        }
    }
    return count;
}

// ***** IMPLEMENT ME! *****
void display_game_state(mcw_game* game) {
    printf("  ");
    for (int i = 0; i < game->width; i++) {
        printf("%2d", i);
    }
    puts("");
    for (int y = 0; y < game->height; y++) {
        printf("%2d", y);
        for (int x = 0; x < game->width; x++) {
            if (game->status[y][x] == hidden) {
                emit_utf_8(HIDDEN);
            }
            else if ( game->status[y][x] == flagged) {
                emit_utf_8(MARKER);
            }
            else {
                if (game->field[y][x] == weeper) {
                    emit_utf_8(WEEPER);
                }
                if (game->field[y][x] == open) {
                    printf("%2d", get_adjacent_weeper_count(game, x, y));
                }
            }
               
        }
        puts("");
    }
}

// ***** IMPLEMENT ME! *****
bool is_in_game_bounds(mcw_game* game, int x, int y) {
    if (x < 0 || y < 0 || x >= game->width || y >= game->height) { return false; }
    return true;
}

// ***** IMPLEMENT ME! *****
void mark_game_square(mcw_game* game, int x, int y) {
    if (is_in_game_bounds(game, x, y)) {
        if (game->status[y][x] == flagged) {  game->status[y][x] = hidden; }
        else if (game->status[y][x] == hidden) { game->status[y][x] = flagged; }
    }
}

// ***** IMPLEMENT ME! *****
void reveal_game_square(mcw_game* game, int x, int y) {
    if (is_in_game_bounds(game, x, y) && game->status[y][x] == hidden) {
        game->status[y][x] = revealed;
        if (game->field[y][x] == open) {
            for (int i = -1; i < 2; i++) {
                for (int j = -1; j < 2; j++) {
                    if (is_in_game_bounds(game, x+i, y+j)) {
                        if (get_adjacent_weeper_count(game, x, y) == 0) {
                            reveal_game_square(game, x+i, y+j);
                        }
                    }
                }
            }
        }
    }   
}

// ***** IMPLEMENT ME! *****
bool is_game_over_loss(mcw_game* game) {
    for (int i = 0; i < game->height; i++) {
        for (int j = 0; j < game->width; j++) {
            if (game->field[i][j] == weeper && game->status[i][j] == revealed) { return true; }
        }
    }
    return false;
}

int unrevealed_bomb_count(mcw_game* game) {
    int count = 0;
    for (int i = 0; i < game->height; i++) {
        for (int j = 0; j < game->width; j++) {
            if (game->field[i][j] == weeper && game->status[i][j] != open) { count++; }
            if (game->field[i][j] == weeper && game->status[i][j] == flagged) { count--; }
        }
    }
    return count;
}

int all_unrevealed_cells_count(mcw_game* game) {
    int count = 0;
    for (int i = 0; i < game->height; i++) {
        for (int j = 0; j < game->width; j++) {
            if (game->status[i][j] == revealed || game->status[i][j] == flagged) { count++; }
        }
    }
    return count;
}

// ***** IMPLEMENT ME! *****
bool is_game_over_win(mcw_game* game) {
    int totalCells = game->width * game->height;
    return (totalCells - all_unrevealed_cells_count(game)) == unrevealed_bomb_count(game);
}
