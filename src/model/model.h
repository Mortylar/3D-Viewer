#ifndef SRC_MODEL_MODEL_H_
#define SRC_MODEL_MODEL_H_

//facade

#include "affine_3d.h"
#include "parser.h"

namespace s21 {
class Model {
  public:
    Model() = default;
    ~Model() = default;

    void ReadFile(const char* file_name);

    void Translation(std::vector<double>& v, double dx, double dy, double dz);
    void Rotation(std::vector<double>& v, double, double, double);
    void Scaling(std::vector<double>& v, double, double, double);
    void Normalize(std::vector<double>& v);

  private:
    Affine3D affine_;
    Parser parser_;
};
}

#endif // SRC_MODEL_MODEL_H_
