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

  void Normalize(std::vector<float> &v);
  void Centring(std::vector<float> &v);

  Matrix4f GetTranslation(float x, float y, float z);
  Matrix4f GetRotation(float x, float y, float z);
  Matrix4f GetScaling(float x, float y, float z);
  Matrix4f GetCentralProjection();   // TODO
  Matrix4f GetParralelProjection();  // TODO

 private:
  const size_t dim_ = 3;

  void CheckDimension(size_t dim);
  void CheckScalingNilpotency(float x_scale, float y_scale, float z_scale);
};
}  // namespace s21

#endif  // SRC_AFFINE_3D_H
