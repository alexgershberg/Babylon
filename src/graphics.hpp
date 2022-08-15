#pragma once

#include <sys/ioctl.h>
#include <unistd.h>

#include <vector>

typedef struct
{
    uint32_t rows;
    uint32_t cols;
    std::vector<std::vector<char>> output;
} WindowBuffer;

WindowBuffer getWindowBuffer();

void render(WindowBuffer &windowBuffer);

void assemble_basic(WindowBuffer &windowBuffer);

void draw_shape(WindowBuffer &windowBuffer);

void drawline(WindowBuffer &windowBuffer, int x1, int y1, int x2, int y2);
