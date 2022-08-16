#include <cmath>
#include <iostream>
#include <sstream>

#include "draw.hpp"
#include "graphics.hpp"

// Taken from: https://stackoverflow.com/questions/23369503/get-size-of-terminal-window-rows-columns
WindowBuffer getWindowBuffer()
{
    struct winsize window;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &window); // Get window rows and columns
    ProjectionMatrix projMat(90, (double)(window.ws_row / window.ws_col), 0.1, 1000);
    WindowBuffer windowBuffer = {window.ws_row, window.ws_col, {}, projMat};
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
void assemblWithRows(WindowBuffer &windowBuffer)
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

void assembleEmpty(WindowBuffer &windowBuffer)
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

void drawShape(WindowBuffer &windowBuffer, std::vector<Vector3D> &mesh)
{
    std::cout << "[DEBUG] Got to drawShape." << std::endl;

    // Draw a star in the middle of the screen.
    int row_middle = floor(windowBuffer.rows / 2);
    int col_middle = floor(windowBuffer.cols / 2);
    windowBuffer.output[row_middle][col_middle] = '*';

    // TODO: IMPLEMENT 3D GRAPHIC LOGIC HERE

    std::vector<Vector3D> projectedVectors;
    auto projMat = ProjectionMatrix(90, windowBuffer.cols / windowBuffer.rows, 0.1, 1000);
    for (auto vec : mesh)
    {
        std::cout << "[DEBUG] For Vector in a mesh?" << std::endl;
        // Project each vector
        // auto projectedVector = vec * projMat;
        // projectedVectors.push_back(projectedVector);
    }

    int debug = 0;

    for (auto projVec : projectedVectors)
    {

        std::cout << "[DEBUG] " << debug << std::endl;
        debug++;
    }
}

void drawPixel(WindowBuffer &windowBuffer, int x, int y, char pixel)
{

    // Silently skip over this pixel if we can't draw it.
    // TODO: Don't silently skip over it. :)
    if (x < windowBuffer.cols && y < windowBuffer.rows)
    {
        windowBuffer.output[windowBuffer.rows - y - 1][x] = pixel;
    }
}

// Bresenham's line algorithm : http://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm
void drawLine(WindowBuffer &windowBuffer, int x1, int y1, int x2, int y2)
{
    // Bresenham's line algorithm
    const bool steep = (abs(y2 - y1) > abs(x2 - x1));
    if (steep)
    {
        std::swap(x1, y1);
        std::swap(x2, y2);
    }

    if (x1 > x2)
    {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    const int dx = x2 - x1;
    const int dy = abs(y2 - y1);

    int error = dx / 2.0;
    const int ystep = (y1 < y2) ? 1 : -1;
    int y = y1;

    const int maxX = x2;

    for (int x = x1; x <= maxX; x++)
    {
        if (steep)
        {
            drawPixel(windowBuffer, x, y, '*');
        }
        else
        {
            drawPixel(windowBuffer, x, y, '*');
        }

        error -= dy;
        if (error < 0)
        {
            y += ystep;
            error += dx;
        }
    }
}
