#include <cmath>
#include <iostream>
#include <sstream>

#include "graphics.hpp"

WindowBuffer getWindowBuffer()
{
    struct winsize window;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &window); // Get window rows and columns
    WindowBuffer windowBuffer = {window.ws_row, window.ws_col};
    return windowBuffer;
}

void render(WindowBuffer &windowBuffer)
{
    auto output = windowBuffer.output;
    for (auto row : output)
    {
        for (auto ch : row)
        {
            std::cout << ch;
        }
    }
    std::cout << std::flush;
}

// Add row numbers to window buffer
void assemble_basic(WindowBuffer &windowBuffer)
{
    std::vector<std::vector<char>> output;
    for (int i = 0; i < windowBuffer.rows; ++i)
    {
        std::stringstream row;
        auto num = std::to_string(i);
        row << num;
        // Get literal lenght of the row num string,
        // and substract that from the total number of pixels we need to populate
        for (int j = 0; j < windowBuffer.cols - num.length(); ++j)
        {
            row << " ";
        }

        std::vector<char> row_vector;
        auto tmp = row.str();

        std::copy(tmp.begin(), tmp.end(), std::back_inserter(row_vector));
        output.push_back(row_vector);
    }
    windowBuffer.output = output;
}

void draw_shape(WindowBuffer &windowBuffer)
{
    auto row_middle = floor(windowBuffer.rows / 2);
    auto col_middle = floor(windowBuffer.cols / 2);

    windowBuffer.output[row_middle][col_middle] = '*';

    drawline(windowBuffer, row_middle + 8, col_middle - 28, row_middle - 8, col_middle - 28);

    drawline(windowBuffer, row_middle + 15, col_middle - 14, row_middle - 15, col_middle - 14);
    drawline(windowBuffer, row_middle - 3, col_middle - 9, row_middle - 3, col_middle - 9);
}

void drawline(WindowBuffer &windowBuffer, int x1, int y1, int x2, int y2)
{
    // Rasterize?
    windowBuffer.output[x1][y1] = 'A';

    windowBuffer.output[x2][y2] = 'B';
}
