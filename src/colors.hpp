#ifndef COLORS_HPP
#define COLORS_HPP

#define BABYLON_WHITE 0
#define BABYLON_BLACK 1
#define BABYLON_PINK 2
#define BABYLON_RED 3
#define BABYLON_GREEN 4
#define BABYLON_BLUE 5

#define HACKER_PAIR_0 121 // Pink Black
#define HACKER_PAIR_1 131 // Red Black
#define HACKER_PAIR_2 141 // Green Black
#define HACKER_PAIR_3 151 // Blue Black

int assembleColorCode(int R, int G, int B);

void initializeBasicColors();

void initializeAdvancedColors();

void makePairs();

#endif
