#include <cmath>

#include "graphics.hpp"

Vector3D operator*(Vector3D const &vector, Matrix const &matrix)
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

                                      // let
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
                                      {-0.5, 0.5, 0.5f}};
    this->verticies = cubeMesh;
}

std::vector<Vector3D> CubeMesh::getDefaultCubeMesh()
{
    return this->verticies;
}

ProjectionMatrix::ProjectionMatrix(double fov, double aspect, double near, double far)
{
    double D2R = M_PI / 180.0;
    double yScale = 1.0 / tan(D2R * fov / 2);
    double xScale = yScale / aspect;
    double nearmfar = near - far;
    std::vector<std::vector<double>> mat = {{xScale, 0, 0, 0},
                                            {0, yScale, 0, 0},
                                            {0, 0, (far + near) / nearmfar, -1},
                                            {0, 0, 2 * far * near / nearmfar, 0}};
    this->matrix = mat;
}

