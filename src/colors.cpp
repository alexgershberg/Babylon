#include <ncurses.h>

#include <cmath>
#include <iostream>
#include <string>

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

    init_color(BABYLON_TEST_COLOR, _convertToNcurs(R), _convertToNcurs(G), _convertToNcurs(B));

    init_pair(BABYLON_TEST_COLOR_PAIR, COLOR_RED, BABYLON_TEST_COLOR);
}

