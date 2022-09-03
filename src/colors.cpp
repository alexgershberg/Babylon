#include <ncurses.h>

#include "colors.hpp"

/*

#define BABYLON_WHITE 0
#define BABYLON_BLACK 1
#define BABYLON_PINK 2
#define BABYLON_GREEN 3
#define BABYLON_BLUE 4
#define BABYLON_RED 5

#define HACKER_PAIR_0 121
#define HACKER_PAIR_1 131
#define HACKER_PAIR_2 131
#define HACKER_PAIR_3 131
#define HACKER_PAIR_4 131

*/

void initializeBasicColors()
{
    if (has_colors())
    {
        start_color();
        init_color(BABYLON_BLACK, 0, 0, 0);
        init_color(BABYLON_PINK, 999, 0, 500);
        init_color(BABYLON_RED, 999, 0, 0);
        init_color(BABYLON_GREEN, 0, 999, 0);
        init_color(BABYLON_BLUE, 0, 0, 999);

        init_pair(HACKER_PAIR_0, BABYLON_PINK, BABYLON_BLACK);
        init_pair(HACKER_PAIR_1, BABYLON_RED, BABYLON_BLACK);
        init_pair(HACKER_PAIR_2, BABYLON_GREEN, BABYLON_BLACK);
        init_pair(HACKER_PAIR_3, BABYLON_BLUE, BABYLON_BLACK);
    }
}
