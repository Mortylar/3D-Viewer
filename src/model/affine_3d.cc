#include "affine_3d.h"

#include <cmath>
#include <stdexcept>

#include <iostream> //TODO remove

void s21::Affine3D::Translation(std::vector<double>& v, double dx, double dy, double dz) {
  size_t size = v.size();
  CheckDimension(size);
  for (size_t i = 0; i < size; i += dim_) {
    v[i + 0] += dx;
    v[i + 1] += dy;
    v[i + 2] += dz;
  }
}

void s21::Affine3D::Rotation(std::vector<double>& v, double x_rad, double y_rad, double z_rad) {
  size_t size = v.size();
  CheckDimension(size);

  for (size_t i = 0; i < size; i += dim_) {
    double x_tmp = v[i + 0];
	double x_rot_1 = sin(x_rad) * v[i + 1] - cos(x_rad) * v[i + 2];
	double x_rot_2 = cos(x_rad) * v[i + 1] + sin(x_rad) * v[i + 2];
	double y_z_rot = cos(y_rad) * x_tmp;

	v[i + 0] = cos(z_rad) * (y_z_rot + sin(y_rad) * x_rot_1) + sin(z_rad) * x_rot_2;
	v[i + 1] = sin(z_rad) * (-y_z_rot - sin(y_rad) * x_rot_1)  + cos(z_rad) * x_rot_2;
	v[i + 2] = x_tmp * sin(y_rad) - x_rot_1 * cos(y_rad);
  }

}

void s21::Affine3D::Scaling(std::vector<double>& v, double x_scale, double y_scale, double z_scale) {
  CheckScalingNilpotency(x_scale, y_scale, z_scale);
  size_t size = v.size();
  CheckDimension(size);

  for (size_t i = 0; i < size; i += dim_) {
    v[i + 0] *= x_scale;
	v[i + 1] *= y_scale;
	v[i + 2] *= z_scale;
  }
}

void s21::Affine3D::Normalize(std::vector<double>& v) {
  size_t size = v.size();
  CheckDimension(size);
  double common_wide = fabs(v[0]);
  for (size_t i = 1; i < size; ++i) {
    if (fabs(v[i]) > common_wide) common_wide = fabs(v[i]);
  }
  if ((common_wide > 1.0) || (common_wide < 0.5))
    Scaling(v, 1.0/common_wide, 1.0/common_wide, 1.0/common_wide);
}

void s21::Affine3D::Centring(std::vector<double>& v) {
  size_t size = v.size();
  CheckDimension(size);
  std::vector<double> min_v{v[0], v[1], v[2]};
  std::vector<double> max_v(min_v);
  for (size_t i = 3; i < size; i += 3) {
    for (size_t j = 0; j < dim_; ++j) {
      if (min_v[j] > v[i + j]) min_v[j] = v[i + j];
      if (max_v[j] < v[i + j]) max_v[j] = v[i + j];
    }
  }
  Translation(v, -(max_v[0]+min_v[0])/2, -(max_v[1]+min_v[1])/2, -(max_v[2]+min_v[2])/2);
}

void s21::Affine3D::CheckScalingNilpotency(double x_scale, double y_scale, double z_scale) {
  const double zero = 0.0;
  if ((zero == x_scale) || (zero == y_scale) || (zero == z_scale)) 
    throw std::invalid_argument("s21::Affine3D::Scaling - one of arguments is zero");
}

void s21::Affine3D::CheckDimension(size_t size) {
  if (!size) throw std::invalid_argument("s21::Affine3D::CheckDimension - Vector is empty");
  if ((size % dim_)) throw std::invalid_argument("s21::Affine3D::CheckDimension -"
                          " vector dimension is not a multiple 3");
}
