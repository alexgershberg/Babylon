#ifndef DRAW_HPP
#define DRAW_HPP

#include <sys/ioctl.h>
#include <unistd.h>

#include <vector>

#include "colors.hpp"
#include "graphics.hpp"

class Pixel
{
  public:
    Pixel();
    explicit Pixel(char value, ColorPair color = BABYLON_RED_COLOR_PAIR);

    char value = ' ';
    ColorPair color;
};

class WindowBuffer
{
  public:
    WindowBuffer();
    uint32_t rows;
    uint32_t cols;
    std::vector<std::vector<Pixel>> output;
};

// https://www.scratchapixel.com/lessons/3d-basic-rendering/rasterization-practical-implementation/rasterization-stage
float edgeFunction(Vector3D const &a, Vector3D const &b, Vector2D const &c);

std::vector<Vector3D> projectVectors(std::vector<Vector3D> &mesh, double fTheta, int width, int height);

void rasterize(WindowBuffer &windowBuffer, Vector3D const &vec1, Vector3D const &vec2, Vector3D const &vec3,
               ColorPair color);

void flush(WindowBuffer &windowBuffer);

void assembleWithRows(WindowBuffer &windowBuffer);

void assembleEmpty(WindowBuffer *windowBuffer);

void drawDebug(WindowBuffer &windowBuffer, std::vector<Vector3D> &mesh, double fTheta);

void drawFps(WindowBuffer &windowBuffer, int frames);

void drawShape(WindowBuffer &windowBuffer, std::vector<Vector3D> &mesh, double fTheta);

void drawLine(WindowBuffer &windowBuffer, Vector2D vec1, Vector2D vec2, ColorPair color);

void drawPixel(WindowBuffer &windowBuffer, int x, int y, Pixel pixel);

#endif
