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
    ProjectionMatrix projMat(90, static_cast<double>(window.ws_row) / static_cast<double>(window.ws_col), 0.1, 1000);
    WindowBuffer windowBuffer = {window.ws_row, window.ws_col, {}, projMat};
    return windowBuffer;
}

void render(WindowBuffer &windowBuffer)
{

    std::string backgroundColor = "\033[?25l\033[48;2;239;0;255m"; // "\033[48;2;{r};{g};{b}m"
    std::string pixelColor = "\033[38;2;0;0;0m";

    std::cout << backgroundColor << pixelColor;

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

void drawShape(WindowBuffer &windowBuffer, std::vector<Vector3D> &mesh, double fTheta)
{

    // TODO: IMPLEMENT 3D GRAPHIC LOGIC HERE

    std::vector<Vector3D> projectedVectors;

    auto projMat = ProjectionMatrix(90, static_cast<double>(windowBuffer.cols) / static_cast<double>(windowBuffer.rows),
                                    0.1, 1000);
    auto rotMatX = RotMatX(fTheta);
    auto rotMatY = RotMatY(fTheta);
    auto rotMatZ = RotMatZ(fTheta);

    for (auto &vec : mesh)
    {
        //        std::cout << "[DEBUG] vec: " << vec.x << " " << vec.y << " " << vec.z << std::endl;

        auto rotVecZ = vec * rotMatZ;
        auto rotVecZX = rotVecZ * rotMatX;
        auto rotVecZXY = rotVecZX * rotMatY;

        rotVecZXY.z += 1;

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

    // Actually put pixels on the screen now.
    for (int i = 0; i < projectedVectors.size(); i += 3)
    {
        // We need to get 3 vectors.
        auto vec1 = projectedVectors[i];
        auto vec2 = projectedVectors[i + 1];
        auto vec3 = projectedVectors[i + 2];

        drawLine(windowBuffer, (int)vec1.x, (int)vec1.y, (int)vec2.x, (int)vec2.y);
        drawLine(windowBuffer, (int)vec2.x, (int)vec2.y, (int)vec3.x, (int)vec3.y);
        drawLine(windowBuffer, (int)vec3.x, (int)vec3.y, (int)vec1.x, (int)vec1.y);

        /*
        std::cout << "[DEBUG] i : " << i << std::endl;
        std::cout << "[DEBUG] vec1 : " << vec1.x << " " << vec1.y << std::endl;
        std::cout << "[DEBUG] vec2 : " << vec2.x << " " << vec2.y << std::endl;
        std::cout << "[DEBUG] vec3 : " << vec3.x << " " << vec3.y << std::endl;
        std::cout << std::endl;
    */
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
            drawPixel(windowBuffer, y, x, '-');
        }
        else
        {
            drawPixel(windowBuffer, x, y, '+');
        }

        error -= dy;
        if (error < 0)
        {
            y += ystep;
            error += dx;
        }
    }
}
