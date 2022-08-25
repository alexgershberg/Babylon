#include <cmath>
#include <iostream>

#include "graphics.hpp"

Vector3D operator*(Vector3D const &vector, ProjectionMatrix const &matrix)
{
    auto x = vector.x * matrix[0][0] + vector.y * matrix[1][0] + vector.z * matrix[2][0] * matrix[3][0];
    auto y = vector.x * matrix[0][1] + vector.y * matrix[1][1] + vector.z * matrix[2][1] * matrix[3][1];
    auto z = vector.x * matrix[0][2] + vector.y * matrix[1][2] + vector.z * matrix[2][2] * matrix[3][2];
    auto w = vector.x * matrix[0][3] + vector.y * matrix[1][3] + vector.z * matrix[2][3] * matrix[3][3];

    if (w != 0.0)
    {
        x = x / w;
        y = y / w;
        z = z / w;
    }

    return Vector3D(x, y, z);
}

Vector3D operator*(Vector3D const &vector, RotMatX const &matrix)
{
    auto x = vector.x * matrix[0][0] + vector.y * matrix[1][0] + vector.z * matrix[2][0] * matrix[3][0];
    auto y = vector.x * matrix[0][1] + vector.y * matrix[1][1] + vector.z * matrix[2][1] * matrix[3][1];
    auto z = vector.x * matrix[0][2] + vector.y * matrix[1][2] + vector.z * matrix[2][2] * matrix[3][2];
    auto w = vector.x * matrix[0][3] + vector.y * matrix[1][3] + vector.z * matrix[2][3] * matrix[3][3];

    if (w != 0.0)
    {
        x = x / w;
        y = y / w;
        z = z / w;
    }

    return Vector3D(x, y, z);
}

Vector3D operator*(Vector3D const &vector, RotMatY const &matrix)
{
    auto x = vector.x * matrix[0][0] + vector.y * matrix[1][0] + vector.z * matrix[2][0] * matrix[3][0];
    auto y = vector.x * matrix[0][1] + vector.y * matrix[1][1] + vector.z * matrix[2][1] * matrix[3][1];
    auto z = vector.x * matrix[0][2] + vector.y * matrix[1][2] + vector.z * matrix[2][2] * matrix[3][2];
    auto w = vector.x * matrix[0][3] + vector.y * matrix[1][3] + vector.z * matrix[2][3] * matrix[3][3];

    if (w != 0.0)
    {
        x = x / w;
        y = y / w;
        z = z / w;
    }

    return Vector3D(x, y, z);
}

Vector3D operator*(Vector3D const &vector, RotMatZ const &matrix)
{
    auto x = vector.x * matrix[0][0] + vector.y * matrix[1][0] + vector.z * matrix[2][0] * matrix[3][0];
    auto y = vector.x * matrix[0][1] + vector.y * matrix[1][1] + vector.z * matrix[2][1] * matrix[3][1];
    auto z = vector.x * matrix[0][2] + vector.y * matrix[1][2] + vector.z * matrix[2][2] * matrix[3][2];
    auto w = vector.x * matrix[0][3] + vector.y * matrix[1][3] + vector.z * matrix[2][3] * matrix[3][3];

    if (w != 0.0)
    {
        x = x / w;
        y = y / w;
        z = z / w;
    }

    return Vector3D(x, y, z);
}

CubeMesh::CubeMesh()
{
    /*
    std::vector<Vector3D> cubeMesh = {// front
                                      {-0.5, 0.5, -0.5},
                                      {-0.5, -0.5, -0.5},
                                      {0.5, -0.5, -0.5},
                                      {-0.5, 0.5, -0.5},
                                      {0.5, -0.5, -0.5},
                                      {0.5, 0.5, -0.5},

                                      // top
                                      {-0.5, -0.5, -0.5},
                                      {-0.5, -0.5, 0.5},
                                      {0.5, -0.5, 0.5},
                                      {-0.5, -0.5, -0.5},
                                      {0.5, -0.5, 0.5},
                                      {0.5, -0.5, -0.5},

                                      // right
                                      {0.5, 0.5, -0.5},
                                      {0.5, -0.5, -0.5},
                                      {0.5, -0.5, 0.5},
                                      {0.5, 0.5, 0.5},
                                      {0.5, -0.5, 0.5},
                                      {0.5, 0.5, 0.5},

                                      // left
                                      {-0.5, 0.5, 0.5},
                                      {-0.5, -0.5, 0.5},
                                      {-0.5, -0.5, -0.5},
                                      {-0.5, 0.5, 0.5},
                                      {-0.5, -0.5, -0.5},
                                      {-0.5, 0.5, -0.5},

                                      // bottom
                                      {-0.5, 0.5, 0.5},
                                      {-0.5, 0.5, -0.5},
                                      {0.5, 0.5, -0.5},
                                      {-0.5, 0.5, 0.5},
                                      {0.5, 0.5, -0.5},
                                      {0.5, 0.5, 0.5},

                                      // back
                                      {0.5, 0.5, 0.5},
                                      {0.5, -0.5, 0.5},
                                      {-0.5, -0.5, 0.5},
                                      {0.5, 0.5, 0.5},
                                      {-0.5, -0.5, 0.5},
                                      {-0.5, 0.5, 0.5}};
                                      */

    std::vector<Vector3D> cubeMesh = {{0.1024f, -0.9435f, 0.3151f},         {0.7002f, -0.6617f, 0.2680f},
                                      {-0.2680f, -0.9435f, 0.1947f},        {-0.2680f, -0.9435f, -0.1947f},
                                      {0.1024f, -0.9435f, -0.3151f},        {0.9050f, -0.3304f, 0.2680f},
                                      {0.0247f, -0.3304f, 0.9435f},         {-0.8897f, -0.3304f, 0.3151f},
                                      {-0.5746f, -0.3304f, -0.7488f},       {0.5346f, -0.3304f, -0.7779f},
                                      {0.8026f, -0.1256f, 0.5831f},         {-0.3066f, -0.1256f, 0.9435f},
                                      {-0.9921f, -0.1256f, 0.0000f},        {-0.3066f, -0.1256f, -0.9435f},
                                      {0.8026f, -0.1256f, -0.5831f},        {0.4089f, 0.6617f, 0.6284f},
                                      {-0.4713f, 0.6617f, 0.5831f},         {-0.7002f, 0.6617f, -0.2680f},
                                      {0.0385f, 0.6617f, -0.7488f},         {0.7240f, 0.6617f, -0.1947f},
                                      {0.2680f, 0.9435f, -0.1947f},         {0.4911f, 0.7947f, -0.3568f},
                                      {0.4089f, 0.6617f, -0.6284f},         {-0.1024f, 0.9435f, -0.3151f},
                                      {-0.1876f, 0.7947f, -0.5773f},        {-0.4713f, 0.6617f, -0.5831f},
                                      {-0.3313f, 0.9435f, 0.0000f},         {-0.6071f, 0.7947f, 0.0000f},
                                      {-0.7002f, 0.6617f, 0.2680f},         {-0.1024f, 0.9435f, 0.3151f},
                                      {-0.1876f, 0.7947f, 0.5773f},         {0.0385f, 0.6617f, 0.7488f},
                                      {0.2680f, 0.9435f, 0.1947f},          {0.4911f, 0.7947f, 0.3568f},
                                      {0.7240f, 0.6617f, 0.1947f},          {0.8897f, 0.3304f, -0.3151f},
                                      {0.7947f, 0.1876f, -0.5773f},         {0.5746f, 0.3304f, -0.7488f},
                                      {-0.0247f, 0.3304f, -0.9435f},        {-0.3035f, 0.1876f, -0.9342f},
                                      {-0.5346f, 0.3304f, -0.7779f},        {-0.9050f, 0.3304f, -0.2680f},
                                      {-0.9822f, 0.1876f, 0.0000f},         {-0.9050f, 0.3304f, 0.2680f},
                                      {-0.5346f, 0.3304f, 0.7779f},         {-0.3035f, 0.1876f, 0.9342f},
                                      {-0.0247f, 0.3304f, 0.9435f},         {0.5746f, 0.3304f, 0.7488f},
                                      {0.7947f, 0.1876f, 0.5773f},          {0.8897f, 0.3304f, 0.3151f},
                                      {0.3066f, 0.1256f, -0.9435f},         {0.3035f, -0.1876f, -0.9342f},
                                      {0.0247f, -0.3304f, -0.9435f},        {-0.8026f, 0.1256f, -0.5831f},
                                      {-0.7947f, -0.1876f, -0.5773f},       {-0.8897f, -0.3304f, -0.3151f},
                                      {-0.8026f, 0.1256f, 0.5831f},         {-0.7947f, -0.1876f, 0.5773f},
                                      {-0.5746f, -0.3304f, 0.7488f},        {0.3066f, 0.1256f, 0.9435f},
                                      {0.3035f, -0.1876f, 0.9342f},         {0.5346f, -0.3304f, 0.7779f},
                                      {0.9921f, 0.1256f, 0.0000f},          {0.9822f, -0.1876f, 0.0000f},
                                      {0.9050f, -0.3304f, -0.2680f},        {0.4713f, -0.6617f, -0.5831f},
                                      {0.1876f, -0.7947f, -0.5773f},        {-0.0385f, -0.6617f, -0.7488f},
                                      {-0.4089f, -0.6617f, -0.6284f},       {-0.4911f, -0.7947f, -0.3568f},
                                      {-0.7240f, -0.6617f, -0.1947f},       {-0.7240f, -0.6617f, 0.1947f},
                                      {-0.4911f, -0.7947f, 0.3568f},        {-0.4089f, -0.6617f, 0.6284f},
                                      {0.7002f, -0.6617f, -0.2680f},        {0.6071f, -0.7947f, 0.0000f},
                                      {0.3313f, -0.9435f, 0.0000f},         {-0.0385f, -0.6617f, 0.7488f},
                                      {0.1876f, -0.7947f, 0.5773f},         {0.4713f, -0.6617f, 0.5831f},
                                      {0.4713f, -0.6617f, 0.5831f}, // temp fix

                                      {0.000000f, -2.500000f, 0.000000f},   {1.809018f, -1.118049f, 1.314313f},
                                      {-0.690970f, -1.118050f, 2.126623f},  {-2.236066f, -1.118039f, 0.000000f},
                                      {-0.690970f, -1.118050f, -2.126623f}, {1.809018f, -1.118049f, -1.314313f},
                                      {0.690970f, 1.118050f, 2.126623f},    {-1.809018f, 1.118049f, 1.314313f},
                                      {-1.809018f, 1.118049f, -1.314313f},  {0.690970f, 1.118050f, -2.126623f},
                                      {2.236066f, 1.118039f, 0.000000f},    {0.000000f, 2.500000f, 0.000000f},
                                      {-0.406139f, -2.126636f, 1.249988f},  {1.063307f, -2.126636f, 0.772529f},
                                      {0.657172f, -1.314344f, 2.022529f},   {2.126620f, -1.314340f, 0.000000f},
                                      {1.063307f, -2.126636f, -0.772529f},  {-1.314324f, -2.126629f, 0.000000f},
                                      {-1.720474f, -1.314341f, 1.249992f},  {-0.406139f, -2.126636f, -1.249988f},
                                      {-1.720474f, -1.314341f, -1.249992f}, {0.657172f, -1.314344f, -2.022529f},
                                      {2.377645f, 0.000000f, 0.772532f},    {2.377645f, 0.000000f, -0.772532f},
                                      {0.000000f, 0.000000f, 2.500000f},    {1.469464f, 0.000000f, 2.022542f},
                                      {-2.377645f, 0.000000f, 0.772532f},   {-1.469464f, 0.000000f, 2.022542f},
                                      {-1.469464f, 0.000000f, -2.022542f},  {-2.377645f, 0.000000f, -0.772532f},
                                      {1.469464f, 0.000000f, -2.022542f},   {0.000000f, 0.000000f, -2.500000f},
                                      {1.720474f, 1.314341f, 1.249992f},    {-0.657172f, 1.314344f, 2.022529f},
                                      {-2.126620f, 1.314340f, 0.000000f},   {-0.657172f, 1.314344f, -2.022529f},
                                      {1.720474f, 1.314341f, -1.249992f},   {0.406139f, 2.126636f, 1.249988f},
                                      {1.314324f, 2.126629f, 0.000000f},    {-1.063307f, 2.126636f, 0.772529f},
                                      {-1.063307f, 2.126636f, -0.772529f},  {0.406139f, 2.126636f, -1.249988f}};

    this->verticies = cubeMesh;
}

std::vector<Vector3D> CubeMesh::getDefaultCubeMesh()
{
    return this->verticies;
}

// Implementation i found only (don't remember where)
ProjectionMatrix::ProjectionMatrix(double fov, double aspect, double near, double far)
{
    //    std::cout << "[DEBUG] Aspect: " << aspect << std::endl;
    double D2R = M_PI / 180.0; // Degrees to radians
    double yScale = 1.0 / tan(D2R * fov / 2);
    double xScale = yScale / aspect;
    double nearmfar = near - far;
    std::vector<std::vector<double>> mat = {
        {xScale, 0, 0, 0},
        {0, yScale, 0, 0},
        {0, 0, (far + near) / nearmfar, -1},
        {0, 0, 2 * far * near / nearmfar, 1},
    };
    this->matrix = mat;
}

/*
ProjectionMatrix::ProjectionMatrix(double fov, double aspect, double near, double far)
{
    double fovRad = 1.0 / tan(fov * 0.5);
    double q = far / (far - near);

    std::vector<std::vector<double>> mat = {
        {aspect * fovRad, 0, 0, 0},
        {0, fovRad, 0, 0},
        {0, 0, q, 1},
        {0, 0, -near * q, 0},
    };

    this->matrix = mat;
}
*/

RotMatX::RotMatX(double fTheta)
{
    auto cosf = cos(fTheta);
    auto sinf = sin(fTheta);
    std::vector<std::vector<double>> mat = {
        {1, 0, 0, 0},
        {0, cosf, -sinf, 0},
        {0, sinf, cosf, 0},
        {0, 0, 0, 1},
    };

    this->matrix = mat;
}

RotMatY::RotMatY(double fTheta)
{
    auto cosf = cos(fTheta);
    auto sinf = sin(fTheta);
    std::vector<std::vector<double>> mat = {
        {cosf, 0, sinf, 0},
        {0, 1, 0, 0},
        {-sinf, 0, cosf, 0},
        {0, 0, 0, 1},
    };

    this->matrix = mat;
}

RotMatZ::RotMatZ(double fTheta)
{
    auto cosf = cos(fTheta);
    auto sinf = sin(fTheta);
    std::vector<std::vector<double>> mat = {
        {cosf, -sinf, 0, 0},
        {sinf, cosf, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
    };

    this->matrix = mat;
}
