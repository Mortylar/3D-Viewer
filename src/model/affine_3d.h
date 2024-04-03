#ifndef SRC_AFFINE_3D_H_
#define SRC_AFFINE_3D_H_

#include <cstddef>
#include <vector>

#include "matrix_4f.h"

namespace s21 {
class Affine3D {
public:
  Affine3D() = default;
  ~Affine3D() = default;

  void Translation(float (&v)[16], float dx, float dy, float dz);
  void Rotation(float (&v)[16], float x_rad, float y_rad, float z_rad);
  void Scaling(float (&v)[16], float x_scale, float y_scale, float z_scale);
  void Normalize(std::vector<float> &v);
  void Centring(std::vector<float> &v);

  Matrix4f GetTranslation(float x, float y, float z);
  Matrix4f GetRotation(float x, float y, float z);
  Matrix4f GetScaling(float x, float y, float z);
  Matrix4f GetProjection(); //TODO

private:
  const size_t dim_ = 3;

  void CheckDimension(size_t dim);
  void CheckScalingNilpotency(float x_scale, float y_scale, float z_scale);
};
} // namespace s21

#endif // SRC_AFFINE_3D_H
