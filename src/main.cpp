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

    // Keep track of fps
    int frames = 0;
    int counted_frames = 0;
    auto fps_previous = std::chrono::system_clock::now();
    while (true)
    {
        int MS_PER_TICK = 50'000; // Microseconds per tick. 1'000'000 ms in a second.

        auto current = std::chrono::system_clock::now();
        auto elapsed = current - previous;
        previous = current;

        lag += elapsed.count();

        auto windowBuffer = WindowBuffer();
        while (lag >= MS_PER_TICK)
        {
            fTheta += 0.02; // Tick()

            lag -= MS_PER_TICK;
        }

        // Calculate the location of the shape itself, and draw it into WindwoBuffer
        CubeMesh cube;
        auto cubeMesh = cube.getDefaultCubeMesh();
        drawShape(windowBuffer, cubeMesh, fTheta);

        // Render FPS Counter when 1 second passes
        auto fps_current = std::chrono::system_clock::now();
        auto fps_elapsed = fps_current - fps_previous;
        if (fps_elapsed.count() >= 1'000'000) // Did 1 second pass? Reset FPS.
        {
            fps_previous = std::chrono::system_clock::now();
            counted_frames = frames;
            frames = 0;
        }

        drawFps(windowBuffer, counted_frames);
        render(windowBuffer);
        frames += 1;
        refresh(); // Refresh the window.
    }

    if (!DEBUG_MODE)
    {
        endwin(); // End curses mode.
    }

    return 0;
}
