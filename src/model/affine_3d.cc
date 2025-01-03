#include "affine_3d.h"

#include <cmath>
#include <stdexcept>

s21::Matrix4f s21::Affine3D::GetTranslation(float x, float y, float z) {
  Matrix4f translation;
  translation(0, 3) = x;
  translation(1, 3) = y;
  translation(2, 3) = z;
  return translation;
}

s21::Matrix4f s21::Affine3D::GetRotation(float x, float y, float z) {
  Matrix4f rotation;

  float sinA = sin(x);
  float sinB = sin(y);
  float sinG = sin(z);
  float cosA = cos(x);
  float cosB = cos(y);
  float cosG = cos(z);

  rotation(0, 0) = cosG * cosB;
  rotation(0, 1) = -sinG * cosB;
  rotation(0, 2) = sinB;
  rotation(0, 3) = 0.f;
  rotation(1, 0) = sinG * cosA + cosG * sinB * sinA;
  rotation(1, 1) = cosG * cosA - sinG * sinB * sinA;
  rotation(1, 2) = -cosB * sinA;
  rotation(1, 3) = 0.0;
  rotation(2, 0) = sinG * sinA - cosG * sinB * cosA;
  rotation(2, 1) = cosG * sinA + sinG * sinB * cosA;
  rotation(2, 2) = cosB * cosA;
  rotation(2, 3) = 0.f;
  rotation(3, 0) = 0.f;
  rotation(3, 1) = 0.f;
  rotation(3, 2) = 0.f;
  rotation(3, 3) = 1.f;
  return rotation;
}

s21::Matrix4f s21::Affine3D::GetScaling(float x, float y, float z) {
  CheckScalingNilpotency(x, y, z);
  Matrix4f scaling;
  scaling(0, 0) = x;
  scaling(1, 1) = y;
  scaling(2, 2) = z;
  return scaling;
}

s21::Matrix4f s21::Affine3D::GetParralelProjection() {
  float near = 1.0;
  float far = 100.0;
  Matrix4f result;
  result(0, 0) = 1;
  result(1, 1) = 1;
  result(2, 2) = 2.0 / (far - near);
  result(2, 3) = (near + far) / (near - far);
  result(3, 3) = 1.0;
  return result;
}

s21::Matrix4f s21::Affine3D::GetCentralProjection() {
  float angle_koef = 1.1917536;  // 1/tan(80/2)
  float near = 1.0;
  float far = 100.0;
  Matrix4f result;
  result(0, 0) = angle_koef;
  result(1, 1) = angle_koef;
  result(2, 2) = -(near + far) / (near - far);
  result(2, 3) = 2 * (far * near) / (near - far);
  result(3, 2) = 1.0;
  result(3, 3) = 0.0;
  return result;
}

void s21::Affine3D::Normalize(std::vector<float> &v) {
  size_t size = v.size();
  CheckDimension(size);
  float common_wide = fabs(v[0]);
  for (size_t i = 1; i < size; ++i) {
    if (fabs(v[i]) > common_wide) common_wide = fabs(v[i]);
  }
  if (common_wide == 0.0) common_wide = 1.0;
  if ((common_wide > 1.0) || (common_wide < 0.5)) {
    for (size_t i = 0; i < v.size(); i += 1) {
      v[i + 0] *= 1.0 / common_wide;
    }
  }
}

void s21::Affine3D::Centring(std::vector<float> &v) {
  size_t size = v.size();
  CheckDimension(size);
  std::vector<float> min_v{v[0], v[1], v[2]};
  std::vector<float> max_v(min_v);
  for (size_t i = 3; i < size; i += 3) {
    for (size_t j = 0; j < dim_; ++j) {
      if (min_v[j] > v[i + j]) min_v[j] = v[i + j];
      if (max_v[j] < v[i + j]) max_v[j] = v[i + j];
    }
  }
  for (size_t i = 0; i < size; i += 3) {
    v[i] -= (max_v[0] + min_v[0]) / 2;
    v[i + 1] -= (max_v[1] + min_v[1]) / 2;
    v[i + 2] -= (max_v[2] + min_v[2]) / 2;
  }
}

void s21::Affine3D::CheckScalingNilpotency(float x_scale, float y_scale,
                                           float z_scale) {
  const float zero = 0.0;
  if ((zero == x_scale) || (zero == y_scale) || (zero == z_scale))
    throw std::invalid_argument(
        "s21::Affine3D::Scaling - one of arguments is zero");
}

void s21::Affine3D::CheckDimension(size_t size) {
  if (!size)
    throw std::invalid_argument(
        "s21::Affine3D::CheckDimension - Vector is empty");
  if ((size % dim_))
    throw std::invalid_argument(
        "s21::Affine3D::CheckDimension -"
        " vector dimension is not a multiple 3");
}
