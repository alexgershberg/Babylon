#include <ncurses.h> // "man ncurses" for manual page

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

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
    double fTheta = 0;
    auto previous = std::chrono::system_clock::now();
    double lag = 0.0;
    while (true)
    {
        int MS_PER_TICK = 20;

        auto current = std::chrono::system_clock::now();
        auto elapsed = current - previous;
        previous = current;

        lag += elapsed.count();

        auto windowBuffer = WindowBuffer();
        while (lag >= MS_PER_TICK)
        {
            fTheta += 0.000001; // Tick()

            lag -= MS_PER_TICK;
        }

        CubeMesh cube;
        auto cubeMesh = cube.getDefaultCubeMesh();
        drawShape(windowBuffer, cubeMesh, fTheta);
        if (!DEBUG_MODE)
        {
            render(windowBuffer);
            refresh(); // Refresh the window.
        }
    }

    if (!DEBUG_MODE)
    {
        endwin(); // End curses mode.
    }

    return 0;
}
