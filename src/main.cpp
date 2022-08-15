#include <iostream>

#include "graphics.hpp"

int main()
{
    // https://stackoverflow.com/questions/23369503/get-size-of-terminal-window-rows-columns
    // std::string color1 = "\033[33;44m";
    // Main rendering loop
    while (true)
    {
        auto windowBuffer = getWindowBuffer();

        std::string color = "\033[?25l\033[48;2;256;120;0m"; // "\033[48;2;{r};{g};{b}m"
        std::cout << color;

        assemble_basic(windowBuffer);
        draw_shape(windowBuffer);
        render(windowBuffer);

        usleep(10000);
    }

    return 0;
}
