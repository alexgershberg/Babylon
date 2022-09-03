#include <ncurses.h>

#include <iostream>
#include <string>

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

int assembleColorCode(int R, int G, int B)
{
    auto Rstr = std::to_string(R);
    auto Gstr = std::to_string(G);
    auto Bstr = std::to_string(B);

    auto formatted = Rstr + Bstr + Gstr;

    return std::stoi(formatted);
}

void initializeBasicColors()
{
    if (!has_colors())
    {
        // Your terminal doesn't support colors.
        return;
    }

    /*
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
    */

    /*
    // Initialize A LOT OF COLORS
    for (int R = 0; R < 1000; R += 100)
    {
        for (int G = 0; G < 1000; G += 100)
        {
            for (int B = 0; B < 1000; B += 100)
            {
                int code = assembleColorCode(R, G, B); // RRR'GGG'BBB
                init_color(code, R, G, B);
            }
        }
    }
*/
    makePairs();
}

void makePairs()
{
    init_pair(666, 1, 2);
}
