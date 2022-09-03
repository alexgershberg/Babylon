#include <ncurses.h>

#include "colors.hpp"

/*

#define BABYLON_WHITE 0
#define BABYLON_BLACK 1
#define BABYLON_PINK 2
#define BABYLON_GREEN 3
#define BABYLON_BLUE 4

#define HACKER_PAIR_0 121
#define HACKER_PAIR_1 131
#define HACKER_PAIR_2 131
#define HACKER_PAIR_3 131
#define HACKER_PAIR_4 131

*/

void initializeColors()
{
    if (has_colors())
    {
        start_color();
        init_color(BABYLON_PINK, 999, 0, 500);
        init_color(BABYLON_GREEN, 0, 255, 0);

        init_pair(HACKER_PAIR_0, OWN_PINK, BABYLON_BLACK);
    }
}
