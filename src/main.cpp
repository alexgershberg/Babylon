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
        int MS_PER_TICK = 16'667; // Microseconds per tick. 1'000'000 ms in a second.
                                  // 1'000'000 / 20 Ticks = 50'000ms per tick. 20 tps.
                                  // 1'000'000 / 60 Ticks = 16'667ms per tick. 60 tps.

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

        // Update FPS Counter when 1 second passes
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
