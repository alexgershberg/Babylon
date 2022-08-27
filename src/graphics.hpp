#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <vector>

class ProjectionMatrix
{
  public:
    ProjectionMatrix(double fov, double aspect, double near, double far);

    std::vector<double> operator[](int i) const
    {
        return matrix[i];
    }

  private:
    std::vector<std::vector<double>> matrix;
};

class RotMatX
{
  public:
    RotMatX(double fTheta);

    std::vector<double> operator[](int i) const
    {
        return matrix[i];
    }

  private:
    std::vector<std::vector<double>> matrix;
};

class RotMatY
{
  public:
    RotMatY(double fTheta);

    std::vector<double> operator[](int i) const
    {
        return matrix[i];
    }

  private:
    std::vector<std::vector<double>> matrix;
};

class RotMatZ
{
  public:
    RotMatZ(double fTheta);

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

    friend Vector3D operator*(Vector3D const &vector, ProjectionMatrix const &matrix);
    friend Vector3D operator*(Vector3D const &vector, RotMatX const &matrix);
    friend Vector3D operator*(Vector3D const &vector, RotMatY const &matrix);
    friend Vector3D operator*(Vector3D const &vector, RotMatZ const &matrix);
    double x, y, z;
};

class Vector2D
{
  public:
    Vector2D(double x, double y) : x{x}, y{y}
    {
    }

    double x, y;
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

// Vector3D MultiplyVec3DByMatrix(Vector3D &vec3d, ProjectionMatrix projMat);

#endif
