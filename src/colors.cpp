#include <ncurses.h>

#include "colors.hpp"

int _convertToNcurs(double colorCode)
{
    return (colorCode / 255) * 999;
}

void initializeBasicColors()
{
    if (!has_colors())
    {
        // Your terminal doesn't support colors.
        return;
    }

    start_color();

    double R, G, B;

    R = 0x00;
    G = 0x00;
    B = 0x00;

    // init_color(BABYLON_TEST_COLOR, _convertToNcurs(R), _convertToNcurs(G), _convertToNcurs(B));

    // init_pair(BABYLON_TEST_COLOR_PAIR, COLOR_RED, BABYLON_TEST_COLOR);

    init_pair(BABYLON_WHITE_COLOR_PAIR, COLOR_WHITE, COLOR_BLACK);
    init_pair(BABYLON_RED_COLOR_PAIR, COLOR_RED, COLOR_BLACK);
    init_pair(BABYLON_GREEN_COLOR_PAIR, COLOR_GREEN, COLOR_BLACK);
    init_pair(BABYLON_BLUE_COLOR_PAIR, COLOR_BLUE, COLOR_BLACK);
}

