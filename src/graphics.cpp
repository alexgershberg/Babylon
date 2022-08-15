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

    std::string color = "\033[?25l\033[48;2;256;120;0m"; // "\033[48;2;{r};{g};{b}m"
    std::cout << color;

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
void assemble_with_rows(WindowBuffer &windowBuffer)
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

void assemble_empty(WindowBuffer &windowBuffer)
{
    std::vector<std::vector<char>> output;
    for (int i = 0; i < windowBuffer.rows; ++i)
    {
        std::stringstream row;
        for (int j = 0; j < windowBuffer.cols; ++j)
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
    int row_middle = floor(windowBuffer.rows / 2);
    int col_middle = floor(windowBuffer.cols / 2);
    windowBuffer.output[row_middle][col_middle] = '*';

    int constIncr = 5;
    drawline(windowBuffer, 0, 0, 20, 50);

    // drawline(windowBuffer, 71, 22, 90, 25);
    // drawline(windowBuffer, col_middle - constIncr, row_middle - constIncr, col_middle + constIncr,
    //         row_middle - constIncr);

    // drawline(windowBuffer, col_middle + constIncr, row_middle - constIncr, col_middle + constIncr,
    //          row_middle + constIncr);

    // drawline(windowBuffer, col_middle + constIncr, row_middle + constIncr, col_middle - constIncr,
    //          row_middle + constIncr);

    // drawline(windowBuffer, col_middle - constIncr, row_middle + constIncr, col_middle - constIncr,
    //          row_middle - constIncr);
}

void drawPixel(WindowBuffer &windowBuffer, int x, int y, char pixel)
{
    windowBuffer.output[windowBuffer.rows - y - 1][x] = pixel;
}

// Algorithm implementing Bresenham's algorithm
void drawline(WindowBuffer &windowBuffer, int x0, int y0, int x1, int y1)
{

    int dx, dy, p, x, y;
    dx = x1 - x0;
    dy = y1 - y0;
    x = x0;
    y = y0;
    p = 2 * dy - dx;
    while (x < x1)
    {
        if (p >= 0)
        {
            drawPixel(windowBuffer, x, y, '*');
            y = y + 1;
            p = p + 2 * dy - 2 * dx;
        }
        else
        {

            drawPixel(windowBuffer, x, y, '*');
            p = p + 2 * dy;
        }
        x = x + 1;
    }
}
