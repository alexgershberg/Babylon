#include <curses.h> // "man ncurses" for manual page

#include <iostream>

#include "draw.hpp"
#include "parameters.hpp"

int main(int argc, char *argv[], char *environ[])
{
    bool DEBUG_MODE = parseParameters(argc, argv, environ);

    // Curses defaults
    if (!DEBUG_MODE)
    {
        initscr(); // Start curses mode.
        nonl();
        cbreak();
        noecho();
    }
    // Main rendering loop
    while (true)
    {
        auto windowBuffer = getWindowBuffer();

        assembleEmpty(windowBuffer);

        CubeMesh cube;
        auto cubeMesh = cube.getDefaultCubeMesh();

        drawShape(windowBuffer, cubeMesh);

        if (!DEBUG_MODE)
        {
            render(windowBuffer);
            refresh(); // Refresh the window.
        }

        usleep(200000);
    }

    if (!DEBUG_MODE)
    {
        endwin(); // End curses mode.
    }

    return 0;
}
