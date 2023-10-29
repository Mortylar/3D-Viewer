#ifndef SRC_AFFINE_3D_H_
#define SRC_AFFINE_3D_H_

#include <vector>
#include <cstddef>

namespace s21 {
class Affine3D {
  public:
    Affine3D() = default;
    ~Affine3D() = default;

    void Translation(std::vector<double>& v, double dx, double dy, double dz);
    void Rotation(std::vector<double>& v, double x_rad, double y_rad, double z_rad);
    void Scaling(std::vector<double>& v, double x_scale, double y_scale, double z_scale);
    void Normalize(std::vector<double>& v);

  private:
    const size_t dim_ = 3;

    void CheckDimension(size_t dim);
    void CheckScalingNilpotency(double x_scale, double y_scale, double z_scale);
};
}

#endif // SRC_AFFINE_3D_H
