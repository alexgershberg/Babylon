#ifndef DRAW_HPP
#define DRAW_HPP

#include <sys/ioctl.h>
#include <unistd.h>

#include <vector>

#include "graphics.hpp"

struct WindowBuffer
{
    uint32_t rows;
    uint32_t cols;
    std::vector<std::vector<char>> output = {};
    ProjectionMatrix projMat;
};

WindowBuffer getWindowBuffer();

void render(WindowBuffer &windowBuffer);

void assembleWithRows(WindowBuffer &windowBuffer);

void assembleEmpty(WindowBuffer &windowBuffer);

void drawShape(WindowBuffer &windowBuffer, std::vector<Vector3D> &mesh, double fTheta);

void drawLine(WindowBuffer &windowBuffer, double x1, double y1, double x2, double y2);

void drawPixel(WindowBuffer &windowBuffer, int x, int y, char pixel);

#endif
