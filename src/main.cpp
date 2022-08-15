#include <functional>
#include <iostream>

#include "graphics.hpp"
#include "parameters.hpp"

int main(int argc, char *argv[], char *environ[])
{
    // https://stackoverflow.com/questions/23369503/get-size-of-terminal-window-rows-columns
    // std::string color1 = "\033[33;44m";
    // Main rendering loop
    bool DEBUG_MODE = parseParameters(argc, argv, environ);

    while (true)
    {
        auto windowBuffer = getWindowBuffer();

        assemble_empty(windowBuffer);
        draw_shape(windowBuffer);
        if (!DEBUG_MODE)
        {
            render(windowBuffer);
        }
        usleep(200000);
    }

    return 0;
}
