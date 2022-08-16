#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <vector>

class Matrix
{
  public:
    Matrix(){};
    Matrix(std::vector<std::vector<double>> m) : matrix(m)
    {
    }

    std::vector<double> operator[](int i) const
    {
        return matrix[i];
    }

  private:
    std::vector<std::vector<double>> matrix;
};

class Vector3D
{
  public:
    Vector3D(double x, double y, double z) : x{x}, y{y}, z{z}
    {
    }

    friend Vector3D operator*(Vector3D const &vector, Matrix const &matrix);
    double x, y, z;
};

/*
class Mesh
{
  public:
    Mesh();

    Mesh(std::vector<Vector3D> &verticies);

    std::vector<Vector3D> getVerticies() const;

  private:
    std::vector<Vector3D> verticies;
};
*/

class CubeMesh
{
  public:
    CubeMesh();

    std::vector<Vector3D> getDefaultCubeMesh();

  private:
    std::vector<Vector3D> verticies;
};

class ProjectionMatrix : public Matrix
{
  public:
    ProjectionMatrix(double fov, double aspect, double near, double far);

  private:
    std::vector<std::vector<double>> matrix;
};

// Vector3D MultiplyVec3DByMatrix(Vector3D &vec3d, ProjectionMatrix projMat);

#endif
