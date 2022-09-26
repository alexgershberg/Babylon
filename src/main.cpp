#include <ncurses.h> // "man ncurses" for manual page

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

#include "colors.hpp"
#include "draw.hpp"
#include "parameters.hpp"

void startncurs(bool DEBUG_MODE)
{
    // Curses defaults
    if (!DEBUG_MODE)
    {
        initscr(); // Start curses mode.
        nonl();
        cbreak();
        noecho();
        curs_set(0); // Disable cursor
        initializeBasicColors();
    }
}

int main(int argc, char *argv[], char *environ[])
{
    bool DEBUG_MODE = parseParameters(argc, argv, environ);

    startncurs(DEBUG_MODE);

    // Main rendering loop : https://gameprogrammingpatterns.com/game-loop.html
    double fTheta = 0; // Variable for tracking 3D model offset

    // Variables for keeping track of FPS
    int frames = 0;
    int counted_frames = 0;
    auto fps_previous = std::chrono::system_clock::now();

    auto previous = std::chrono::system_clock::now();
    double lag = 0.0;

    while (true)
    {
        int MS_PER_TICK = 50'000; // Microseconds per tick. 1'000'000 ms in a second.
                                  // 1'000'000 / 20 Ticks = 50'000ms per tick. 20 tps.
                                  // 1'000'000 / 60 Ticks = 16'667ms per tick. 60 tps.

        auto current = std::chrono::system_clock::now();
        auto elapsed = current - previous;
        previous = current;

        lag += elapsed.count();

        while (lag >= MS_PER_TICK)
        {
            fTheta += 0.1; // Tick()

            lag -= MS_PER_TICK;
        }

        auto windowBuffer = WindowBuffer();

        // Calculate the location of the shape itself, and draw it into WindwoBuffer
        CubeMesh cube;
        auto cubeMesh = cube.getDefaultCubeMesh();
        drawShape(windowBuffer, cubeMesh, fTheta);
        // drawDebug(windowBuffer, cubeMesh, fTheta);

        // TODO: To support more colors in the future, we could write a subroutine
        // to colors defined in the mesh, but not yet initialised. Would also need to keep track of initialized colors.

        // Update FPS Counter when 1 second passes
        auto fps_current = std::chrono::system_clock::now();
        auto fps_elapsed = fps_current - fps_previous;
        if (fps_elapsed.count() >= 1'000'000) // Did 1 second pass? Reset FPS.
        {
            fps_previous = std::chrono::system_clock::now();
            counted_frames = frames;
            frames = 0;
        }

        if (!DEBUG_MODE)
        {
            drawFps(windowBuffer, counted_frames);

            flush(windowBuffer); // Flush the WindowBuffer to ostream
            refresh();           // Refresh the window.

            frames += 1;
        }
    }

    if (!DEBUG_MODE)
    {
        endwin(); // End curses mode.
    }

    return 0;
}
