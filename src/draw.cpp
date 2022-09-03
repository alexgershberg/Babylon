#include <ncurses.h>

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

#include "draw.hpp"
#include "graphics.hpp"

WindowBuffer::WindowBuffer()
{
    struct winsize window; // Taken from:
                           // https://stackoverflow.com/questions/23369503/get-size-of-terminal-window-rows-columns
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &window); // Get window rows and columns
    rows = window.ws_row;
    cols = window.ws_col;

    // Assemble empty. TODO: Or we could assemble with row numbers
    assembleEmpty(this);
};

Pixel::Pixel(char value, uint32_t BRGB) : value{value}, BRGB{BRGB}
{
}

float edgeFunction(Vector3D const &a, Vector3D const &b, Vector2D const &c)
{
    return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
}

std::vector<Vector3D> projectVectors(std::vector<Vector3D> &mesh, double fTheta, int width, int height)
{
    std::vector<Vector3D> projectedVectors;

    auto projMat = ProjectionMatrix(90, static_cast<double>(width) / static_cast<double>(height), 0.1, 1000);
    auto rotMatX = RotMatX(fTheta);
    auto rotMatY = RotMatY(fTheta * 0.2);
    auto rotMatZ = RotMatZ(fTheta * 0.1);

    for (auto &vec : mesh)
    {
        auto rotVecZ = vec * rotMatZ;
        auto rotVecZX = rotVecZ * rotMatX;
        auto rotVecZXY = rotVecZX * rotMatY;

        // Push object forwards into view TODO: This should be done by keyboard input
        rotVecZXY.z += 2;

        // Project each vector
        auto projectedVector = rotVecZXY * projMat;

        // Force scale into view
        projectedVector.x += 1;
        projectedVector.y += 1;

        // Adjust for screen width and height (place it in the middle of the screen)
        projectedVector.x *= 0.5 * static_cast<double>(width);
        projectedVector.y *= 0.5 * static_cast<double>(height);

        projectedVectors.push_back(projectedVector);
    }

    return projectedVectors;
}

void rasterize(WindowBuffer &windowBuffer, Vector3D const &vec1, Vector3D const &vec2, Vector3D const &vec3)
{
}

void render(WindowBuffer &windowBuffer)
{
    char noCursor[] = "\033[?25l";
    char backgroundColor[] = "\033[48;2;0;0;0m"; // "\033[48;2;{r};{g};{b}m"
    char pixelColor[] = "\033[38;2;38;255;0m";   // Foreground color "\033[38;2;{r};{g};{b}m"
    // char reset[] = "\033[0m";
    // char clear[] = "\033[2J";

    // char red[] = "\033[38;2;255;0;0m";
    // ESC[<line>;<column>f // Move cursor to line # and column #

    auto output = windowBuffer.output;

    printf("%s%s%s", noCursor, backgroundColor, pixelColor);
    for (auto row : output)
    {
        for (auto pixel : row)
        {
            addch(pixel.value);
        }
    }
    move(0, 0);
}

/*
TODO: Needs to be updated to support "Pixels"

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

*/

void assembleEmpty(WindowBuffer *windowBuffer)
{
    std::vector<std::vector<Pixel>> output;
    for (int i = 0; i < windowBuffer->rows; ++i)
    {
        std::vector<Pixel> row_vector;
        for (int j = 0; j < windowBuffer->cols; ++j)
        {
            row_vector.push_back(Pixel(' ', 0));
        }

        output.push_back(row_vector);
    }
    windowBuffer->output = output;
}

void drawFps(WindowBuffer &windowBuffer, int frames)
{
    drawPixel(windowBuffer, 0, 0, Pixel('F', 0));
    drawPixel(windowBuffer, 1, 0, Pixel('P', 0));
    drawPixel(windowBuffer, 2, 0, Pixel('S', 0));
    drawPixel(windowBuffer, 3, 0, Pixel(':', 0));
    drawPixel(windowBuffer, 4, 0, Pixel(' ', 0));

    auto fps_string = std::to_string(frames);
    int i = 5;
    for (auto ch : fps_string)
    {
        drawPixel(windowBuffer, i, 0, Pixel(ch, 0));
        i++;
    }
}

void drawShape(WindowBuffer &windowBuffer, std::vector<Vector3D> &mesh, double fTheta)
{

    // TODO: IMPLEMENT 3D GRAPHIC LOGIC HERE
    std::vector<Vector3D> projectedVectors = projectVectors(mesh, fTheta, windowBuffer.cols, windowBuffer.rows);

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
    windowBuffer.output[row_middle][col_middle] = Pixel('*', 0);
}

void drawPixel(WindowBuffer &windowBuffer, int x, int y, Pixel pixel)
{
    // Skip over this pixel if we can't draw it. (Out of bounds)
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
            drawPixel(windowBuffer, y, x, Pixel(',', 0));
        }
        else
        {
            drawPixel(windowBuffer, x, y, Pixel('.', 0));
        }

        error -= dy;
        if (error < 0)
        {
            y += ystep;
            error += dx;
        }
    }
}
