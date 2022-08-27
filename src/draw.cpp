#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

#include "draw.hpp"
#include "graphics.hpp"

// Taken from: https://stackoverflow.com/questions/23369503/get-size-of-terminal-window-rows-columns
WindowBuffer getWindowBuffer()
{
    struct winsize window;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &window); // Get window rows and columns
    ProjectionMatrix projMat(90, static_cast<double>(window.ws_row) / static_cast<double>(window.ws_col), 0.1, 1000);
    WindowBuffer windowBuffer = {window.ws_row, window.ws_col, {}, projMat};
    return windowBuffer;
}

void render(WindowBuffer &windowBuffer)
{

    std::string backgroundColor = "\033[?25l\033[48;2;239;0;255m"; // "\033[48;2;{r};{g};{b}m"
    std::string pixelColor = "\033[38;2;0;0;0m";
    std::string reset = "\033[0m";
    std::string clear = "\033[2J";

    // ESC[<line>;<column>f          // Move cursor to line # and column #

    auto output = windowBuffer.output;

    /* V2
     *

    std::stringstream out;
    for (int i = 0; i < output.size(); ++i)
    {
        auto &row = output[i]; for (int j = 0; j < row.size(); ++j)
        {
            std::string draw = "\033[<" + std::to_string(i) + ">;<" + std::to_string(j) + ">f" + output[i][j];
            out << draw;
        }
    }

    std::cout << out.str();

    */

    std::cout << backgroundColor << pixelColor;
    for (auto row : output)
    {
        for (auto ch : row)
        {
            std::cout << ch;
            //            usleep(5);
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

void drawShape(WindowBuffer &windowBuffer, std::vector<Vector3D> &mesh, double fTheta)
{

    // TODO: IMPLEMENT 3D GRAPHIC LOGIC HERE

    std::vector<Vector3D> projectedVectors;

    auto projMat = ProjectionMatrix(90, static_cast<double>(windowBuffer.cols) / static_cast<double>(windowBuffer.rows),
                                    0.1, 1000);
    auto rotMatX = RotMatX(fTheta);
    auto rotMatY = RotMatY(fTheta * 0.2);
    auto rotMatZ = RotMatZ(fTheta * 0.1);

    for (auto &vec : mesh)
    {
        auto rotVecZ = vec * rotMatZ;
        auto rotVecZX = rotVecZ * rotMatX;
        auto rotVecZXY = rotVecZX * rotMatY;

        // Push object forwards into view TODO: This should be done by keyboard input
        rotVecZXY.z += 3.5;

        // Project each vector
        auto projectedVector = rotVecZXY * projMat;

        // Force scale into view
        projectedVector.x += 1;
        projectedVector.y += 1;

        // Adjust for screen width and height (place it in the middle of the screen)
        projectedVector.x *= 0.5 * static_cast<double>(windowBuffer.cols);
        projectedVector.y *= 0.5 * static_cast<double>(windowBuffer.rows);

        projectedVectors.push_back(projectedVector);
    }

    std::cout << std::endl;
    // Actually put pixels on the screen now.
    for (int i = 0; i < projectedVectors.size(); i += 3)
    {
        // We need to get 3 vectors.
        auto vec1 = projectedVectors[i];
        auto vec2 = projectedVectors[i + 1];
        auto vec3 = projectedVectors[i + 2];

        drawLine(windowBuffer, vec1.x, vec1.y, vec2.x, vec2.y);
        drawLine(windowBuffer, vec2.x, vec2.y, vec3.x, vec3.y);
        drawLine(windowBuffer, vec3.x, vec3.y, vec1.x, vec1.y);
    }

    // Draw a star in the middle of the screen.
    int row_middle = floor(windowBuffer.rows / 2);
    int col_middle = floor(windowBuffer.cols / 2);
    windowBuffer.output[row_middle][col_middle] = '*';
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
void drawLine(WindowBuffer &windowBuffer, double x1, double y1, double x2, double y2)
{
    // Bresenham's line algorithm
    const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
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

    const double dx = x2 - x1;
    const double dy = fabs(y2 - y1);

    double error = dx / 2.0f;
    const int ystep = (y1 < y2) ? 1 : -1;
    int y = (int)y1;

    const int maxX = (int)x2;

    for (int x = (int)x1; x <= maxX; x++)
    {
        if (steep)
        {
            drawPixel(windowBuffer, y, x, 'q');
        }
        else
        {
            drawPixel(windowBuffer, x, y, 'b');
        }

        error -= dy;
        if (error < 0)
        {
            y += ystep;
            error += dx;
        }
    }
}
