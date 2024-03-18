#ifndef SRC_AFFINE_3D_H_
#define SRC_AFFINE_3D_H_

#include <vector>
#include <cstddef>

namespace s21 {
class Affine3D {
  public:
    Affine3D() = default;
    ~Affine3D() = default;

    void Translation(std::vector<float>& v, float dx, float dy, float dz);
    void Rotation(std::vector<float>& v, float x_rad, float y_rad, float z_rad);
    void Scaling(std::vector<float>& v, float x_scale, float y_scale, float z_scale);
    void Normalize(std::vector<float>& v);
    void Centring(std::vector<float> & v);

  private:
    const size_t dim_ = 3;

    void CheckDimension(size_t dim);
    void CheckScalingNilpotency(float x_scale, float y_scale, float z_scale);
};
}

#endif // SRC_AFFINE_3D_H
