#include <ncurses.h>

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

#include "colors.hpp"
#include "draw.hpp"
#include "graphics.hpp"

WindowBuffer::WindowBuffer()
{
    struct winsize window;                     // Taken from:
                                               // https://stackoverflow.com/questions/23369503/get-size-of-terminal-window-rows-columns
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &window); // Get window rows and columns
    rows = window.ws_row;
    cols = window.ws_col;

    // Assemble empty. TODO: Or we could assemble with row numbers
    assembleEmpty(this);
};

Pixel::Pixel(char value, ColorPair color) : value{value}, color{color}
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
        rotVecZXY.z += 5.5;

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

// TODO: Add a bounding box later to improve performance of this algorithm
void rasterize(WindowBuffer &windowBuffer, Vector3D const &vec0, Vector3D const &vec1, Vector3D const &vec2,
               ColorPair color)
{
    for (double i = 0; i < windowBuffer.rows; i++)
    {
        for (double j = 0; j < windowBuffer.cols; j++)
        {
            Vector2D point = {j, i};

            float w0 = edgeFunction(vec1, vec2, point);
            float w1 = edgeFunction(vec2, vec0, point);
            float w2 = edgeFunction(vec0, vec1, point);

            if (w0 >= 0 && w1 >= 0 && w2 >= 0)
            {
                drawPixel(windowBuffer, j, i, Pixel('.', color));
            }
        }
    }
}

void flush(WindowBuffer &windowBuffer)
{
    auto output = windowBuffer.output;

    for (auto row : output)
    {
        for (auto pixel : row)
        {

            attron(COLOR_PAIR(pixel.color));

            addch(pixel.value);

            attroff(COLOR_PAIR(pixel.color));
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
            row_vector.push_back(Pixel(' '));
        }

        output.push_back(row_vector);
    }
    windowBuffer->output = output;
}

// Temp Testing function
void drawDebug(WindowBuffer &windowBuffer, std::vector<Vector3D> &mesh, double fTheta)
{
    std::vector<Vector3D> projectedVectors = projectVectors(mesh, fTheta, windowBuffer.cols, windowBuffer.rows);

    for (int i = 0; i < projectedVectors.size(); i += 3)
    {
        auto vec0 = projectedVectors[i];
        auto vec1 = projectedVectors[i + 1];
        auto vec2 = projectedVectors[i + 2];

        rasterize(windowBuffer, vec0, vec1, vec2, BABYLON_WHITE_COLOR_PAIR);
    }
}

void drawFps(WindowBuffer &windowBuffer, int frames)
{
    // Yeah, i'm hardcoding "FPS: ". Don't you have anything else TODO:?
    drawPixel(windowBuffer, 0, 0, Pixel('F'));
    drawPixel(windowBuffer, 1, 0, Pixel('P'));
    drawPixel(windowBuffer, 2, 0, Pixel('S'));
    drawPixel(windowBuffer, 3, 0, Pixel(':'));
    drawPixel(windowBuffer, 4, 0, Pixel(' '));

    auto fps_string = std::to_string(frames);
    int i = 5;
    for (auto ch : fps_string)
    {
        drawPixel(windowBuffer, i, 0, Pixel(ch));
        i++;
    }
}

void drawShape(WindowBuffer &windowBuffer, std::vector<Vector3D> &mesh, double fTheta)
{
    std::vector<Vector3D> projectedVectors = projectVectors(mesh, fTheta, windowBuffer.cols, windowBuffer.rows);

    // Actually put pixels on the screen now.
    for (int i = 0; i < projectedVectors.size(); i += 3)
    {
        // We need to get 3 vectors.
        Vector3D vec3d1 = projectedVectors[i];
        Vector3D vec3d2 = projectedVectors[i + 1];
        Vector3D vec3d3 = projectedVectors[i + 2];

        Vector2D vec2d1 = {vec3d1.x, vec3d1.y};
        Vector2D vec2d2 = {vec3d2.x, vec3d2.y};
        Vector2D vec2d3 = {vec3d3.x, vec3d3.y};

        drawLine(windowBuffer, vec2d1, vec2d2, BABYLON_RED_COLOR_PAIR);
        drawLine(windowBuffer, vec2d2, vec2d3, BABYLON_GREEN_COLOR_PAIR);
        drawLine(windowBuffer, vec2d3, vec2d1, BABYLON_BLUE_COLOR_PAIR);
    }

    // Draw a star in the middle of the screen.
    int row_middle = floor(windowBuffer.rows / 2);
    int col_middle = floor(windowBuffer.cols / 2);
    windowBuffer.output[row_middle][col_middle] = Pixel('*');
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
void drawLine(WindowBuffer &windowBuffer, Vector2D vec1, Vector2D vec2, ColorPair color)
{
    double x1 = vec1.x;
    double y1 = vec1.y;

    double x2 = vec2.x;
    double y2 = vec2.y;

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
            drawPixel(windowBuffer, y, x, Pixel('$', color));
        }
        else
        {
            drawPixel(windowBuffer, x, y, Pixel('@', color));
        }

        error -= dy;
        if (error < 0)
        {
            y += ystep;
            error += dx;
        }
    }
}
